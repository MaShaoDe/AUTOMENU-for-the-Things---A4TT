//
//  config_loader.c
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
//  add or modify:
//  22.01.2026  Loads menu configuration from a text file
//  22.01.2026  Menu configuration loader with validation
//  22.01.2026  Menu configuration loader with strict validation
//  22.01.2026  Includes line-numbered error reporting
//
/* … gleicher Header wie zuvor … */

//
//  config_loader.c
//
//  Menu configuration loader with strict validation
//  Includes line-numbered error reporting
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "config_loader.h"

/* helpers */

static char *strdup_safe(const char *s)
{
    if (!s) return NULL;
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

static menu_t *find_menu(menu_t *menus, size_t count, const char *id)
{
    for (size_t i = 0; i < count; i++) {
        if (strcmp(menus[i].id, id) == 0)
            return &menus[i];
    }
    return NULL;
}

/* validation */

static int validate_menus(menu_t *menus, size_t menu_count)
{
    for (size_t i = 0; i < menu_count; i++) {
        for (size_t j = i + 1; j < menu_count; j++) {
            if (strcmp(menus[i].id, menus[j].id) == 0) {
                fprintf(stderr,
                        "Config error: duplicate menu id '%s'\n",
                        menus[i].id);
                return 0;
            }
        }
    }

    for (size_t i = 0; i < menu_count; i++) {
        for (size_t k = 0; k < menus[i].item_count; k++) {
            menu_item_t *it = &menus[i].items[k];
            if (it->type != MENU_ITEM_SUBMENU)
                continue;

            if (!it->submenu_id) {
                fprintf(stderr,
                        "Config error: submenu without id (menu '%s')\n",
                        menus[i].id);
                return 0;
            }

            if (!find_menu(menus, menu_count, it->submenu_id)) {
                fprintf(stderr,
                        "Config error: submenu '%s' not found (referenced in menu '%s')\n",
                        it->submenu_id, menus[i].id);
                return 0;
            }
        }
    }
    return 1;
}

/* public API */

int load_menu_config(
    const char *path,
    menu_t **out_menus,
    size_t *out_menu_count
)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        perror("open config");
        return 0;
    }

    menu_t *menus = NULL;
    size_t menu_count = 0;
    menu_t *current_menu = NULL;

    char line[512];
    size_t line_no = 0;

    while (fgets(line, sizeof(line), f)) {
        line_no++;
        char *p = line;
        while (isspace((unsigned char)*p)) p++;

        if (*p == '\0' || *p == '#')
            continue;

        if (strncmp(p, "menu", 4) == 0) {
            char id[128], title[256];
            if (sscanf(p, "menu %127s \"%255[^\"]\"", id, title) != 2) {
                fprintf(stderr,
                        "Config error (line %zu): invalid menu definition\n",
                        line_no);
                goto fail;
            }

            menus = realloc(menus, sizeof(menu_t) * (menu_count + 1));
            current_menu = &menus[menu_count];
            memset(current_menu, 0, sizeof(menu_t));

            current_menu->id = strdup_safe(id);
            current_menu->title = strdup_safe(title);
            current_menu->items = NULL;
            current_menu->item_count = 0;

            menu_count++;
            continue;
        }

        if (strncmp(p, "item", 4) == 0 && current_menu) {
            char label[256], type[64], value[128] = {0};
            int n = sscanf(p, "item \"%255[^\"]\" %63s %127s", label, type, value);

            if (n < 2) {
                fprintf(stderr,
                        "Config error (line %zu): invalid item syntax\n",
                        line_no);
                goto fail;
            }

            current_menu->items = realloc(
                current_menu->items,
                sizeof(menu_item_t) * (current_menu->item_count + 1)
            );

            menu_item_t *it =
                &current_menu->items[current_menu->item_count];
            memset(it, 0, sizeof(menu_item_t));
            it->label = strdup_safe(label);

            if (strcmp(type, "action") == 0) {
                if (n != 3) {
                    fprintf(stderr,
                            "Config error (line %zu): action requires id\n",
                            line_no);
                    goto fail;
                }
                it->type = MENU_ITEM_ACTION;
                it->action_id = strdup_safe(value);

            } else if (strcmp(type, "submenu") == 0) {
                if (n != 3) {
                    fprintf(stderr,
                            "Config error (line %zu): submenu requires id\n",
                            line_no);
                    goto fail;
                }
                it->type = MENU_ITEM_SUBMENU;
                it->submenu_id = strdup_safe(value);

            } else if (strcmp(type, "back") == 0) {
                if (n != 2) {
                    fprintf(stderr,
                            "Config error (line %zu): back takes no arguments\n",
                            line_no);
                    goto fail;
                }
                it->type = MENU_ITEM_BACK;

            } else if (strcmp(type, "exit") == 0) {
                if (n != 2) {
                    fprintf(stderr,
                            "Config error (line %zu): exit takes no arguments\n",
                            line_no);
                    goto fail;
                }
                it->type = MENU_ITEM_EXIT;

            } else if (strcmp(type, "info") == 0) {
                if (n != 2) {
                    fprintf(stderr,
                            "Config error (line %zu): info takes no arguments\n",
                            line_no);
                    goto fail;
                }
                it->type = MENU_ITEM_INFO;

            } else {
                fprintf(stderr,
                        "Config error (line %zu): unknown item type '%s'\n",
                        line_no, type);
                goto fail;
            }

            current_menu->item_count++;
            continue;
        }

        fprintf(stderr,
                "Config error (line %zu): unexpected content\n",
                line_no);
        goto fail;
    }

    fclose(f);

    if (!validate_menus(menus, menu_count)) {
        free_menu_config(menus, menu_count);
        return 0;
    }

    *out_menus = menus;
    *out_menu_count = menu_count;
    return 1;

fail:
    fclose(f);
    free_menu_config(menus, menu_count);
    return 0;
}

void free_menu_config(menu_t *menus, size_t menu_count)
{
    if (!menus) return;

    for (size_t i = 0; i < menu_count; i++) {
        free((char *)menus[i].id);
        free((char *)menus[i].title);

        for (size_t j = 0; j < menus[i].item_count; j++) {
            free((char *)menus[i].items[j].label);
            free((char *)menus[i].items[j].action_id);
            free((char *)menus[i].items[j].submenu_id);
        }
        free(menus[i].items);
    }
    free(menus);
}
