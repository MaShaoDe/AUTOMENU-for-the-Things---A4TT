//
//  core_test.c
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
// „Phase A verification“

#include <stdio.h>
#include "core.h"

static void print_state(core_t *core)
{
    const menu_view_t *view = core_get_current_menu(core);

    if (!view) {
        printf("No active menu\n\n");
        return;
    }

    printf("Menu: %s (%s)\n", view->id, view->title);
    printf("Selected index: %zu\n", view->current_index);

    for (size_t i = 0; i < view->item_count; i++) {
        printf("  %c %zu: %s\n",
               (i == view->current_index) ? '>' : ' ',
               i,
               view->items[i].label);
    }
    printf("\n");
}

int main(void)
{
    menu_item_t main_items[] = {
        { .label = "About",    .action_id = "about",    .submenu_id = NULL },
        { .label = "Settings", .action_id = NULL,       .submenu_id = "settings" }
    };

    menu_item_t settings_items[] = {
        { .label = "Reset", .action_id = "reset", .submenu_id = NULL },
        { .label = "Back",  .action_id = "back",  .submenu_id = NULL }
    };

    menu_t menus[] = {
        {
            .id = "main",
            .title = "Main Menu",
            .items = main_items,
            .item_count = 2
        },
        {
            .id = "settings",
            .title = "Settings",
            .items = settings_items,
            .item_count = 2
        }
    };

    core_t *core = core_create();
    if (!core) {
        printf("Core allocation failed\n");
        return 1;
    }

    if (!core_load(core, menus, 2, "main")) {
        printf("Core load failed\n");
        core_destroy(core);
        return 1;
    }

    print_state(core);

    core_input(core, CORE_EVENT_DOWN);
    print_state(core);

    core_input(core, CORE_EVENT_SELECT);
    print_state(core);

    core_input(core, CORE_EVENT_SELECT);

    const char *action = core_poll_action(core);
    if (action) {
        printf("Action triggered: %s\n\n", action);
    }

    core_select_index(core, 1);

    action = core_poll_action(core);
    if (action) {
        printf("Action triggered: %s\n\n", action);
    }

    core_destroy(core);
    return 0;
}
