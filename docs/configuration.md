# Automenu for the Things – Configuration

## 1. Purpose

This document describes the configuration system used by *Automenu for the Things*.

It defines the structure, responsibilities and behavior of configuration files,
including menu configuration, display configuration and recovery mechanisms.

---

## 2. Configuration Overview

Automenu uses multiple configuration files with clearly separated responsibilities.

At minimum, the following configuration types exist:

- menu configuration
- display configuration
- factory default configuration

Configuration files are human-readable and intended to be edited manually
or via Automenu itself.

---

## 3. Configuration Files

### 3.1 Menu Configuration

The menu configuration defines:

- which menus exist
- menu hierarchy
- menu entries
- actions and submenus

The menu configuration describes *what* the system offers,
not *how* it is rendered.

Typical filename examples:

- `menu.conf`
- `menu.json`

The exact file format may differ by platform,
but the logical menu model is identical everywhere.

---

### 3.2 Display Configuration

The display configuration defines:

- display profiles
- colors and background handling
- rendering behavior
- output-related feature toggles

The display configuration describes *how* Automenu is rendered,
not which functionality exists.

Typical filename examples:

- `display.conf`
- `display.cfg`

---

### 3.3 Factory Default Configuration

A factory default configuration always exists.

Characteristics:

- never modified at runtime
- never overwritten
- shipped with the system
- used as a guaranteed recovery anchor

Typical filename examples:

- `menu.factory`
- `display.factory`

---

## 4. Separation of Responsibilities

Menu configuration and display configuration are strictly separated.

Reasons:

- menu logic must not depend on visual appearance
- display errors must not break system navigation
- recovery must be possible even with broken display settings

No configuration file may implicitly override another.

---

## 5. Human-Readable Configuration

Configuration files are designed for human editing.

Design rules:

- simple and explicit structure
- clear key-value semantics
- comment support
- no implicit or hidden behavior

Complex logic is handled in code, not pushed into configuration syntax.

---

## 6. Comments and Feature Toggles

Configuration files support comments.

Comments may be used to:

- document intent
- temporarily disable settings
- explain non-obvious values

Feature toggles are expressed explicitly through configuration keys.
Commenting out a line disables it implicitly.

---

## 7. Display Profile Selection

Display profiles are defined in the display configuration.

A display profile defines:

- background handling
- default text color
- highlight color
- status color
- error color

Exactly one profile is active at any time.

Profile selection may occur:

- via configuration file
- via Automenu configuration menu
- via startup parameters

---

## 8. Configuration Editing via Automenu

Automenu allows configuration to be edited from within the menu system.

Allowed operations include:

- changing configuration values
- enabling or disabling options
- selecting display profiles
- saving or discarding changes

Configuration editing is a first-class feature,
not a hidden or restricted mode.

---

## 9. Saving Configuration

When configuration changes are saved, Automenu performs the following steps:

1. the current active configuration is renamed to `.bak`
2. the new configuration is written as a complete file
3. the new configuration is validated
4. the configuration is reloaded

Partial writes are not permitted.

---

## 10. Invalid Configuration Handling

If a configuration file cannot be parsed or validated:

- the file is preserved for inspection
- it is renamed to indicate failure
- factory defaults are loaded automatically

The system must remain operable at all times.

---

## 11. Reset to Factory Defaults

Automenu supports resetting configuration to factory defaults.

Reset behavior:

- current configuration is backed up
- factory configuration becomes active
- configuration is reloaded
- a clear status message is displayed

This operation must always be available via startup parameters.

---

## 12. Startup Parameter Overrides

Startup parameters may override configuration settings.

Rules:

- startup parameters always take precedence
- overrides are temporary unless explicitly saved
- recovery-related parameters cannot be disabled

Startup parameters provide guaranteed recovery paths.

---

## 13. Platform-Specific Storage

Configuration storage depends on the platform:

- embedded systems may store configuration in flash
- Unix systems typically store configuration under `/etc`
  or `/usr/local/etc`
- development environments may use local directories

Storage locations must be documented per platform.

---

## 14. Configuration Versioning

Configuration formats evolve conservatively.

Rules:

- backward compatibility is preferred
- incompatible changes require explicit migration
- factory defaults reflect the current format version

Configuration versioning is handled explicitly and carefully.

---

## 15. Summary

The Automenu configuration system is designed to be:

- explicit
- human-readable
- repairable
- platform-independent

Configuration freedom is balanced by guaranteed recovery mechanisms.

