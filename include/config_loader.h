//
//  config_loader.h
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <stddef.h>
#include "menu.h"

/*
 * Loads menu configuration from a text file.
 *
 * Returns 1 on success, 0 on failure.
 * On success, out_menus and out_menu_count are set.
 */
int load_menu_config(
    const char *path,
    menu_t **out_menus,
    size_t *out_menu_count
);

/*
 * Frees all memory allocated by load_menu_config.
 */
void free_menu_config(
    menu_t *menus,
    size_t menu_count
);

#endif
