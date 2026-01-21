//
//  menu.c
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
#include "menu.h"
#include <stdio.h>

/*
 * Example action.
 * Version 0.1.0: visible but harmless.
 */
static void action_dummy(void)
{
    printf("Action executed\n");
    fflush(stdout);
}

/* Menu items */
static menu_item_t main_menu_items[] = {
    {
        .label = "First action",
        .type = MENU_ITEM_ACTION,
        .action = action_dummy,
        .submenu = NULL
    },
    {
        .label = "Second action",
        .type = MENU_ITEM_ACTION,
        .action = action_dummy,
        .submenu = NULL
    }
};

/* Main menu definition */
menu_t main_menu = {
    .title = "Main Menu",
    .items = main_menu_items,
    .item_count = sizeof(main_menu_items) / sizeof(main_menu_items[0])
};
#include <stdio.h>
#include "menu.h"

/*
 * Render menu to stdout.
 * Version 0.1.0: static, read-only rendering.
 */
void menu_render(const menu_t *menu)
{
    if (!menu) {
        return;
    }

    printf("\n%s\n", menu->title);
    printf("--------------------\n");

    for (size_t i = 0; i < menu->item_count; i++) {
        printf("%zu) %s\n", i + 1, menu->items[i].label);
    }

    fflush(stdout);
}
