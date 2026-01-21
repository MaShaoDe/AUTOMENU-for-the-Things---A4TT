//
//  config_loader_test.c
//  
//
//  Created by Marcel Sauder on 22.01.2026.
//

#include <stdio.h>
#include <stdlib.h>

#include "config_loader.h"

int main(void)
{
    menu_t *menus = NULL;
    size_t menu_count = 0;

    if (!load_menu_config("menu.txt", &menus, &menu_count)) {
        printf("Failed to load menu.txt\n");
        return 1;
    }

    printf("Loaded %zu menus\n\n", menu_count);

    for (size_t i = 0; i < menu_count; i++) {
        const menu_t *m = &menus[i];
        printf("Menu: %s (%s)\n", m->id, m->title);

        for (size_t j = 0; j < m->item_count; j++) {
            const menu_item_t *it = &m->items[j];
            printf("  Item: %s", it->label);

            if (it->action_id) {
                printf("  action=%s", it->action_id);
            }
            if (it->submenu_id) {
                printf("  submenu=%s", it->submenu_id);
            }
            printf("\n");
        }
        printf("\n");
    }

    free_menu_config(menus, menu_count);
    return 0;
}
