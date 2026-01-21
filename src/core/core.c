//
//  core.c
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
#include <string.h>
#include "core.h"
#include <stdlib.h>
#include <stdbool.h>


struct core {
    const menu_t *menus;
    size_t menu_count;

    const menu_t *current_menu;
    size_t current_index;

    const char *pending_action;
};

void core_init(core_t *core)
{
    memset(core, 0, sizeof(*core));
}

static const menu_t *find_menu(const core_t *core, const char *id)
{
    for (size_t i = 0; i < core->menu_count; i++) {
        if (strcmp(core->menus[i].id, id) == 0) {
            return &core->menus[i];
        }
    }
    return NULL;
}

int core_load(core_t *core,
               const menu_t *menus,
               size_t menu_count,
               const char *start_menu_id)
{
    core->menus = menus;
    core->menu_count = menu_count;
    core->current_menu = find_menu(core, start_menu_id);
    core->current_index = 0;
    core->pending_action = NULL;

    return core->current_menu != NULL;
}

void core_input(core_t *core, core_event_t event)
{
    if (!core->current_menu) return;

    if (event == CORE_EVENT_UP) {
        if (core->current_index > 0)
            core->current_index--;
    } else if (event == CORE_EVENT_DOWN) {
        if (core->current_index + 1 < core->current_menu->item_count)
            core->current_index++;
    } else if (event == CORE_EVENT_SELECT) {
        core_select_index(core, core->current_index);
    }
}

void core_select_index(core_t *core, size_t index)
{
    if (!core->current_menu) return;
    if (index >= core->current_menu->item_count) return;

    const menu_item_t *item = &core->current_menu->items[index];

    if (item->action_id) {
        core->pending_action = item->action_id;
    } else if (item->submenu_id) {
        const menu_t *submenu = find_menu(core, item->submenu_id);
        if (submenu) {
            core->current_menu = submenu;
            core->current_index = 0;
        }
    }
}

const menu_view_t *core_get_current_menu(const core_t *core)
{
    static menu_view_t view;

    if (!core->current_menu) return NULL;

    view.id = core->current_menu->id;
    view.title = core->current_menu->title;
    view.items = core->current_menu->items;
    view.item_count = core->current_menu->item_count;
    view.current_index = core->current_index;

    return &view;
}

const char *core_poll_action(core_t *core)
{
    const char *a = core->pending_action;
    core->pending_action = NULL;
    return a;
}
core_t *core_create(void)
{
    core_t *core = malloc(sizeof(*core));
    if (!core) return NULL;

    core_init(core);
    return core;
}

void core_destroy(core_t *core)
{
    free(core);
}
