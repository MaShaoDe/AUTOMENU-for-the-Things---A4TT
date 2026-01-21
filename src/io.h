//
//  io.h
//  
//
//  Created by Marcel Sauder on 21.01.2026.
//
#ifndef AUTOMENU_IO_H
#define AUTOMENU_IO_H

#include "automenu.h"

/*
 * Initialize IO subsystem.
 * Returns 0 on success, non-zero on error.
 */
int io_init(automenu_context_t *ctx);

/*
 * Shutdown IO subsystem and restore terminal state.
 */
void io_shutdown(automenu_context_t *ctx);

#endif /* AUTOMENU_IO_H */
/*
 * Read a single key from input.
 * Returns the character read, or -1 on error.
 */
int io_read_key(void);


