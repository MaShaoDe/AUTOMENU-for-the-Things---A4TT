# ARCHITECTURE

## Automenu – Architecture Status v0.1.0
### by Marcel Sauder 2026

## Purpose
This document describes the architecture of Automenu and the design decisions behind it.

Automenu is intentionally built as a small, deterministic framework. Its architecture prioritises clarity, predictability and portability over feature density.

## Design Principles

Automenu follows a strict set of principles:

- deterministic behaviour
- clear separation of responsibilities
- no hidden side effects
- no implicit platform assumptions
- configuration is data, not logic

These principles ensure that the core can be reused unchanged across very different environments, from desktop terminals to embedded systems.

## High-Level Overview

Automenu is composed of four main parts:

- Core
- Configuration Loader
- Adapters
- Action Dispatcher

Each part has a clearly defined responsibility and does not overlap with the others.

## Core

The core is a pure state machine.

It is responsible for:

- holding the menu structure
- tracking the current menu and selection
- handling navigation events
- managing the menu stack
- exposing triggered actions and informational events
- signalling a requested program exit

The core deliberately does **not**:

- read input
- render output
- access the filesystem
- parse configuration files
- perform any system-level actions

The core operates exclusively on structured data and input events. This makes it deterministic, easy to test and independent of the target platform.

## Menu Model

Menus consist of typed menu items. Each menu item has an explicit semantic meaning.

Supported menu item types in v0.1.0 are:

- `action`  
  Triggers an action identified by a string ID.

- `submenu`  
  Switches to another menu.

- `back`  
  Returns to the previous menu on the stack.

- `exit`  
  Requests a controlled program termination.

- `info`  
  Displays informational text without changing menu state.

Each type is handled explicitly by the core. There is no implicit or fallback behaviour.

## Configuration Loader

The configuration loader is responsible for transforming a text-based menu definition into structured menu data.

Its responsibilities include:

- parsing the configuration file
- validating syntax
- validating semantic correctness
- checking submenu references
- rejecting invalid configurations early

The loader is intentionally strict. Invalid configurations cause immediate failure with clear, line-numbered error messages.

This strictness avoids undefined behaviour at runtime and makes configuration errors easy to diagnose.

## Adapters

Adapters connect the core to a concrete environment.

Typical adapter responsibilities include:

- reading user input
- rendering menus
- displaying actions and informational messages
- defining runtime policies

Adapters are free to interpret the core state in any way appropriate for the platform, for example:

- terminal rendering
- serial console output
- graphical displays
- remote interfaces

The adapter is also the correct place for policy decisions.

## Exit Policy

Automenu distinguishes between two exit mechanisms:

- Soft Exit  
  Triggered by a menu item of type `exit`.  
  This is part of the menu model and handled by the core.

- Hard Exit  
  Triggered by a secret key sequence (for example `.q`).  
  This is **not** part of the menu model and is handled exclusively by the adapter.

Hard exit support is controlled at compile time and can be enabled or disabled depending on the target environment.

This separation allows the same codebase to support both open development systems and locked-down kiosk or embedded systems.

## Action Dispatcher

The action dispatcher is the only component that assigns meaning to action identifiers.

It maps string-based action IDs to concrete behaviour.

By design:

- the core does not know what an action does
- the configuration only references action IDs
- the dispatcher defines behaviour explicitly

This keeps the core neutral and allows different platforms to implement actions differently without changing the menu logic.

## Determinism and Testability

Because the core is isolated from IO and platform details, it can be tested independently.

Given the same initial state and the same sequence of input events, the core will always produce the same result.

This property is essential for:

- embedded systems
- long-running kiosk applications
- safety-relevant environments
- reproducible debugging

## Version Status

The architecture described in this document corresponds to **Automenu v0.1.0**.

The core architecture is considered stable and frozen. Future extensions are expected to build on this foundation without breaking the existing design principles.
