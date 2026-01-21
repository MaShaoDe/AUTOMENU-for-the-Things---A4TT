//
//  core.h
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
/*
 * Automenu Core API
 *
 * Version: v0.1.x
 *
 * The core is a deterministic, platform-independent menu state machine.
 * It does not perform IO, rendering, parsing or execution.
 * It only processes input events and exposes state and actions.
 */
#ifndef AUTOMENU_CORE_H
#define AUTOMENU_CORE_H

#include <stddef.h>
#include "menu.h"

/*
 * Core opaque type
 */
typedef struct core core_t;

/*
 * Input events handled by the core
 */
typedef enum {
    CORE_EVENT_UP,
    CORE_EVENT_DOWN,
    CORE_EVENT_SELECT
} core_event_t;

/*
 * Menu view exposed by the core
 */
typedef struct {
    const char *id;
    const char *title;
    const menu_item_t *items;
    size_t item_count;
    size_t current_index;
} menu_view_t;

/*
 * Core lifecycle
 */
core_t *core_create(void);
void core_destroy(core_t *core);

/*
 * Load menus into the core
 */
int core_load(
    core_t *core,
    const menu_t *menus,
    size_t menu_count,
    const char *start_menu_id
);

/*
 * Input handling
 */
void core_input(core_t *core, core_event_t event);
void core_select_index(core_t *core, size_t index);

/*
 * State inspection
 */
const menu_view_t *core_get_current_menu(const core_t *core);

/*
 * Action polling
 */
const char *core_poll_action(core_t *core);

#endif
