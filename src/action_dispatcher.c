//
//  action_dispatcher.c
//  
//
//  Created by Marcel Sauder on 22.01.2026.
//
//  21.01.2026 Visible action dispatcher stub
//  22.01.2026 Phase C – confirms action execution deterministically
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "action_dispatcher.h"

/*
 * Dispatch an action by id.
 *
 * Current behaviour:
 * - visibly confirms the action
 * - waits for a keypress
 * - does NOT perform real logic yet
 *
 * This is intentional and architecture-safe.
 */
void dispatch_action(const char *action_id)
{
    if (!action_id)
        return;

    /* clear screen */
    write(STDOUT_FILENO, "\033[2J\033[H", 7);

    printf("Action triggered:\n\n");
    printf("  %s\n\n", action_id);
    printf("Press any key to continue...\n");
    fflush(stdout);

    char tmp;
    read(STDIN_FILENO, &tmp, 1);
}
