//
//  config_loader.c
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_loader.h"
#define MAX_LINE 512

typedef struct {
    menu_t *menus;
    size_t menu_count;
} menu_accu_t;

static int add_menu(menu_accu_t *accu, const char *id, const char *title)
{
    menu_t *tmp = realloc(accu->menus, (accu->menu_count + 1) * sizeof(menu_t));
    if (!tmp)
        return 0;

    accu->menus = tmp;

    /* >>> HIER war der Fehler: m muss deklariert werden <<< */
    menu_t *m = &accu->menus[accu->menu_count];
    memset(m, 0, sizeof(menu_t));

    m->id = strdup(id);
    m->title = strdup(title);
    m->items = NULL;
    m->item_count = 0;

    if (!m->id || !m->title)
        return 0;

    accu->menu_count++;
    return 1;
}

static int add_item(
    menu_t *menu,
    const char *label,
    const char *action_id,
    const char *submenu_id
)
{
    menu_item_t *tmp =
        realloc(menu->items, (menu->item_count + 1) * sizeof(menu_item_t));
    if (!tmp)
        return 0;

    menu->items = tmp;

    menu_item_t *it = &menu->items[menu->item_count];
    memset(it, 0, sizeof(menu_item_t));

    it->label = strdup(label);
    it->action_id = action_id ? strdup(action_id) : NULL;
    it->submenu_id = submenu_id ? strdup(submenu_id) : NULL;

    if (!it->label)
        return 0;

    menu->item_count++;
    return 1;
}

int load_menu_config(
    const char *path,
    menu_t **out_menus,
    size_t *out_menu_count
)
{
    FILE *f = fopen(path, "r");
    if (!f)
        return 0;

    menu_accu_t accu;
    memset(&accu, 0, sizeof(accu));

    menu_t *current_menu = NULL;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '\n')
            continue;

        if (strncmp(line, "menu ", 5) == 0) {
            char id[64];
            char title[256];

            if (sscanf(line, "menu %63s \"%255[^\"]\"", id, title) != 2)
                goto error;

            if (!add_menu(&accu, id, title))
                goto error;

            current_menu = &accu.menus[accu.menu_count - 1];
        }
        else if (strncmp(line, "  item ", 7) == 0) {
            if (!current_menu)
                goto error;

            char label[256];
            char type[32];
            char value[64];

            if (sscanf(
                    line,
                    "  item \"%255[^\"]\" %31s %63s",
                    label, type, value
                ) != 3)
                goto error;

            if (strcmp(type, "action") == 0) {
                if (!add_item(current_menu, label, value, NULL))
                    goto error;
            }
            else if (strcmp(type, "submenu") == 0) {
                if (!add_item(current_menu, label, NULL, value))
                    goto error;
            }
            else {
                goto error;
            }
        }
        else {
            goto error;
        }
    }

    fclose(f);

    *out_menus = accu.menus;
    *out_menu_count = accu.menu_count;
    return 1;

error:
    fclose(f);
    free_menu_config(accu.menus, accu.menu_count);
    return 0;
}

void free_menu_config(menu_t *menus, size_t menu_count)
{
    if (!menus)
        return;

    for (size_t i = 0; i < menu_count; i++) {
        menu_t *m = &menus[i];

        free((char *)m->id);
        free((char *)m->title);

        for (size_t j = 0; j < m->item_count; j++) {
            free((char *)m->items[j].label);
            free((char *)m->items[j].action_id);
            free((char *)m->items[j].submenu_id);
        }

        free(m->items);
    }

    free(menus);
}
