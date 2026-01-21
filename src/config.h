//
//  config.h
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
#ifndef AUTOMENU_CONFIG_H
#define AUTOMENU_CONFIG_H

#include "automenu.h"

/*
 * Load configuration from persistent storage.
 * Returns 0 on success, non-zero on error.
 */
int config_load(automenu_context_t *ctx);

/*
 * Load factory default configuration.
 * Returns 0 on success, non-zero on error.
 */
int config_load_default(automenu_context_t *ctx);

/*
 * Backup current configuration.
 * Best-effort operation, no return value.
 */
void config_backup(automenu_context_t *ctx);

#endif /* AUTOMENU_CONFIG_H */

