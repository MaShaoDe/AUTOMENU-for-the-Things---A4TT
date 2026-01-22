# Automenu for the Things

### by Marcel Sauder, 2026

Automenu is a small, deterministic menu framework for terminal-based and embedded environments.

At its core is a platform-independent state machine that processes input events and exposes the current menu state as well as triggered actions. Rendering, input handling, IO and configuration formats are deliberately kept outside of the core and are implemented via adapters.

The project is designed so that the core remains testable, predictable and independent of the target platform.

## Features

* platform-independent, deterministic menu core
* strict separation of core logic, configuration and adapters
* support for submenus and hierarchical navigation
* actions triggered via explicit string identifiers
* navigation via cursor movement and direct index selection
* no IO, rendering or parsing logic inside the core
* strict configuration validation with line-numbered error messages
* optional hidden hard exit for development environments
* suitable for FreeBSD, Linux, macOS and embedded targets such as ESP32

## Project Structure

include/core.h
Public core API

src/core/core.c
Menu core implementation (state machine)

src/config_loader.c
Menu configuration loader and validator

src/action_dispatcher.c
Action dispatcher (maps action IDs to behaviour)

src/terminal.c
Terminal adapter (input, rendering, policy)

## Build and Modes

Automenu intentionally uses a minimal build process without a build system.

### Development / Desktop Mode

This mode is intended for development, debugging and interactive terminal usage.

Characteristics:

* menu-based soft exit via `exit`
* additional hidden hard exit via the secret key sequence `.q`
* suitable for FreeBSD, Linux and macOS

Build command:

cc -DALLOW_HARD_EXIT -Iinclude 
src/core/core.c 
src/config_loader.c 
src/action_dispatcher.c 
src/terminal.c 
-o automenu

### Kiosk / Embedded Mode

This mode is intended for closed systems where leaving the program must be explicitly controlled.

Characteristics:

* no hidden hard exit
* exit only possible if explicitly defined in the menu
* suitable for kiosk systems and embedded targets such as ESP32

Build command:

cc -Iinclude 
src/core/core.c 
src/config_loader.c 
src/action_dispatcher.c 
src/terminal.c 
-o automenu

## Usage

./automenu menu.txt

## Terminal Controls

* Arrow Up / Arrow Down
  Move the cursor

* Enter
  Select current menu item

* 1–9
  Direct menu item selection

* .q
  Hidden hard exit (development mode only)

Exit behaviour depends on both the build mode and the menu definition.

## Menu Model

Menu items are explicitly typed and carry a clear semantic meaning.

* action
  Triggers an action via the action dispatcher

* submenu
  Enters a submenu

* back
  Returns to the previous menu

* exit
  Requests a controlled program exit

* info
  Displays informational text without changing menu state

## Architecture Overview

Automenu follows a strict separation of responsibilities.

### Core

The core is a pure state machine. It processes input events and updates menu state accordingly.

The core deliberately contains no assumptions about:

* input devices
* rendering
* operating systems
* hardware

This makes the core deterministic, portable and easy to test.

### Configuration Loader

The configuration loader parses menu definitions from a text file and validates them strictly.

Validation includes:

* syntax checking
* duplicate menu detection
* submenu reference validation

On error, loading is aborted with a clear message including the line number.

### Terminal Adapter

The terminal adapter is responsible for:

* reading input
* rendering menus
* displaying actions and info items
* defining runtime policies

Exit behaviour is intentionally defined here, not in the core.

### Action Dispatcher

The action dispatcher is the only component that assigns meaning to action identifiers.

It maps string-based action IDs to concrete behaviour. This keeps the core completely neutral.

## Exit Behaviour

Automenu distinguishes between two exit mechanisms.

* Soft Exit
  Triggered via a menu item of type `exit`

* Hard Exit
  Triggered via a secret key sequence `.q`

The hard exit:

* is not visible in menus
* is not part of the configuration
* is controlled at compile time
* exists only in the adapter layer

This allows the same codebase to support both open development systems and locked-down kiosk environments.

## Configuration

Menus are defined declaratively in a text-based configuration file.

The configuration language is intentionally strict and non-tolerant of errors. Invalid configurations are rejected early and explicitly.

## Project Status

The architecture and core behaviour are frozen.

Current version: v0.1.0

## License

See LICENSE.
