//
//  menu.h
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
// 22.01.2026 New Menu item EXIT

#ifndef MENU_H
#define MENU_H

#include <stddef.h>

/*
 * Menu item type.
 */
typedef enum {
    MENU_ITEM_ACTION,
    MENU_ITEM_SUBMENU,
    MENU_ITEM_BACK,
    MENU_ITEM_EXIT,
    MENU_ITEM_INFO
} menu_item_type_t;

/*
 * Menu item definition.
 */
typedef struct menu_item {
    const char *label;
    menu_item_type_t type;

    /* Used if type == MENU_ITEM_ACTION */
    const char *action_id;

    /* Used if type == MENU_ITEM_SUBMENU */
    const char *submenu_id;
} menu_item_t;

/*
 * Menu definition.
 */
typedef struct menu {
    const char *id;
    const char *title;
    menu_item_t *items;
    size_t item_count;
} menu_t;

#endif
