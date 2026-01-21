//
//  config.c
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
#include "config.h"

/*
 * Minimal configuration load stub.
 * Version 0.1.0: no file access yet.
 */
int config_load(automenu_context_t *ctx)
{
    (void)ctx;
    return 0;
}

/*
 * Minimal factory default configuration loader.
 */
int config_load_default(automenu_context_t *ctx)
{
    (void)ctx;
    return 0;
}

/*
 * Minimal configuration backup stub.
 */
void config_backup(automenu_context_t *ctx)
{
    (void)ctx;
}

