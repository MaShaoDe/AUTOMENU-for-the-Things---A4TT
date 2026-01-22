//
//  core.c
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
//  22.01.2026 Core menu logic with menu stack
//  22.01.2026 Core menu engine with stack-based navigation
//  Automenu Core Implementation
//  Deterministic, platform-independent menu state machine
/* … gleicher Header wie zuvor … */
#include <stdlib.h>
#include <string.h>
#include "core.h"

#define CORE_MENU_STACK_MAX 16

struct core {
    const menu_t *menus;
    size_t menu_count;

    size_t current_menu;
    size_t current_index;

    size_t menu_stack[CORE_MENU_STACK_MAX];
    size_t stack_depth;

    const char *pending_action;
    const char *pending_info;
    int exit_requested;
};

static size_t find_menu_index(
    const menu_t *menus,
    size_t menu_count,
    const char *menu_id
)
{
    for (size_t i = 0; i < menu_count; i++) {
        if (strcmp(menus[i].id, menu_id) == 0)
            return i;
    }
    return (size_t)-1;
}

core_t *core_create(void)
{
    return calloc(1, sizeof(core_t));
}

void core_destroy(core_t *core)
{
    free(core);
}

int core_load(
    core_t *core,
    const menu_t *menus,
    size_t menu_count,
    const char *start_menu_id
)
{
    if (!core || !menus || !start_menu_id || menu_count == 0)
        return 0;

    size_t idx = find_menu_index(menus, menu_count, start_menu_id);
    if (idx == (size_t)-1)
        return 0;

    core->menus = menus;
    core->menu_count = menu_count;
    core->current_menu = idx;
    core->current_index = 0;
    core->stack_depth = 0;
    core->pending_action = NULL;
    core->pending_info = NULL;
    core->exit_requested = 0;
    return 1;
}

void core_input(core_t *core, core_event_t event)
{
    if (!core) return;
    const menu_t *menu = &core->menus[core->current_menu];

    switch (event) {
        case CORE_EVENT_UP:
            if (core->current_index > 0) core->current_index--;
            break;

        case CORE_EVENT_DOWN:
            if (core->current_index + 1 < menu->item_count)
                core->current_index++;
            break;

        case CORE_EVENT_SELECT: {
            const menu_item_t *item = &menu->items[core->current_index];
            switch (item->type) {
                case MENU_ITEM_ACTION:
                    core->pending_action = item->action_id;
                    break;

                case MENU_ITEM_SUBMENU: {
                    size_t next = find_menu_index(
                        core->menus, core->menu_count, item->submenu_id);
                    if (next != (size_t)-1 &&
                        core->stack_depth < CORE_MENU_STACK_MAX) {
                        core->menu_stack[core->stack_depth++] =
                            core->current_menu;
                        core->current_menu = next;
                        core->current_index = 0;
                    }
                    break;
                }

                case MENU_ITEM_BACK:
                    if (core->stack_depth > 0) {
                        core->current_menu =
                            core->menu_stack[--core->stack_depth];
                        core->current_index = 0;
                    }
                    break;

                case MENU_ITEM_EXIT:
                    core->exit_requested = 1;
                    break;

                case MENU_ITEM_INFO:
                    core->pending_info = item->label;
                    break;
            }
            break;
        }
    }
}

void core_select_index(core_t *core, size_t index)
{
    if (!core) return;
    const menu_t *menu = &core->menus[core->current_menu];
    if (index >= menu->item_count) return;
    core->current_index = index;
    core_input(core, CORE_EVENT_SELECT);
}

const menu_view_t *core_get_current_menu(const core_t *core)
{
    if (!core) return NULL;
    static menu_view_t view;
    const menu_t *menu = &core->menus[core->current_menu];
    view.id = menu->id;
    view.title = menu->title;
    view.items = menu->items;
    view.item_count = menu->item_count;
    view.current_index = core->current_index;
    return &view;
}

const char *core_poll_action(core_t *core)
{
    if (!core) return NULL;
    const char *a = core->pending_action;
    core->pending_action = NULL;
    return a;
}

const char *core_poll_info(core_t *core)
{
    if (!core) return NULL;
    const char *i = core->pending_info;
    core->pending_info = NULL;
    return i;
}

int core_should_exit(core_t *core)
{
    return core ? core->exit_requested : 0;
}
