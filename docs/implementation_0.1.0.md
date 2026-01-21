# Automenu for the Things – Implementation Plan 0.1.0

## 1. Purpose

This document defines the binding implementation plan for Automenu for the Things version 0.1.0.

It serves as the bridge between conceptual documentation and actual source code.
Everything defined in this document is considered authoritative for the 0.1.0 implementation.

Anything not listed here is explicitly out of scope for version 0.1.0.

---

## 2. Scope Definition for Version 0.1.0

Version 0.1.0 delivers a minimal but complete Automenu system that runs in a Unix terminal.

Included:

* core menu engine
* stack-based navigation
* static menu definition loaded from configuration
* ASCII-only rendering
* keyboard input via stdin
* basic paging for long menus
* configuration loading and validation
* configuration backup on save
* startup parameters:

  * `--safe`
  * `--default`
  * `--config`

Explicitly excluded:

* color support
* display profiles
* Telnet support
* ESP32 support
* ncurses
* interactive configuration editor
* packaging systems (Ports, Homebrew)

---

## 3. Binding Code Skeleton

The following source tree structure is binding for version 0.1.0:

```
automenu/
├── src/
│   ├── main.c
│   ├── core.c
│   ├── core.h
│   ├── menu.c
│   ├── menu.h
│   ├── io.c
│   ├── io.h
│   ├── config.c
│   └── config.h
│
├── include/
│   └── automenu.h
│
├── examples/
│   └── menu.conf
│
├── docs/
│   └── implementation_0.1.0.md
│
├── Makefile
└── README.md
```

No additional source files may be added for version 0.1.0.

---

## 4. Module Responsibilities

### 4.1 main.c

Responsibilities:

* program entry point
* parse command-line arguments
* select startup mode
* initialize configuration
* start core loop
* handle clean shutdown

No menu logic is allowed in `main.c`.

---

### 4.2 core.c / core.h

Responsibilities:

* core event loop
* menu state stack
* navigation control
* dispatch menu actions

The core module must not perform IO or rendering directly.

---

### 4.3 menu.c / menu.h

Responsibilities:

* menu data structures
* menu entries and hierarchy
* paging logic
* selection handling

The menu module is purely logical and contains no IO code.

---

### 4.4 io.c / io.h

Responsibilities:

* read single-character input from stdin
* write text to stdout
* clear screen
* basic terminal reset

Only ASCII output is allowed.

---

### 4.5 config.c / config.h

Responsibilities:

* load configuration files
* validate configuration structure
* provide default configuration
* create backup files (`.bak`)

Configuration parsing must be deterministic and strict.

---

## 5. Implementation Order

The following implementation order is mandatory:

1. buildable empty skeleton (all files compile)
2. Makefile
3. IO module (minimal)
4. menu data structures
5. core loop without configuration
6. static in-code menu for testing
7. configuration loader
8. replace static menu with configuration-based menu
9. startup parameter handling

No step may be skipped.

---

## 6. Codex Usage Rules

Codex may be used under the following conditions:

Allowed:

* generating boilerplate C files
* generating header guards
* generating simple structs and enums
* implementing IO wrapper functions

Not allowed:

* designing core logic
* inventing behavior
* changing scope
* adding features not listed in this document

Codex output must always be reviewed and understood before being committed.

---

## 7. Definition of Done for 0.1.0

Version 0.1.0 is considered complete when:

* the program builds without warnings
* a menu defined in `examples/menu.conf` is displayed
* keyboard navigation works
* the program exits cleanly
* broken configuration falls back to defaults
* startup parameters behave as specified

---

## 8. Change Policy

This document is frozen for version 0.1.0.

Any change requires:

* explicit discussion
* documented rationale
* version bump of this file

---

## 9. Summary

This document defines the exact technical contract for Automenu 0.1.0.

It prevents scope creep, guides implementation and ensures that documentation and code evolve together.

