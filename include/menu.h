//
//  menu.h
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
#ifndef MENU_H
#define MENU_H

#include <stddef.h>

/*
 * Menu item definition.
 * Each item either triggers an action (action_id)
 * or navigates to a submenu (submenu_id).
 */
typedef struct menu_item {
    const char *label;
    const char *action_id;
    const char *submenu_id;
} menu_item_t;

/*
 * Menu definition.
 * A menu consists of an id, a title and a list of items.
 */
typedef struct menu {
    const char *id;
    const char *title;
    menu_item_t *items;
    size_t item_count;
} menu_t;

#endif

