# Automenu for the Things – Technical Specification

## 1. Scope

This document defines the technical specification of *Automenu for the Things*.

It describes the architecture, core concepts, menu model, rendering behavior,
configuration handling and recovery mechanisms.

This document is normative.
If other documentation contradicts this specification, this document prevails.

---

## 2. Design Goals

Automenu is designed to:

- run on embedded devices and Unix systems
- provide identical behavior across platforms
- avoid graphical user interfaces and web technologies
- remain understandable, debuggable and repairable
- follow classic Unix tool principles

Non-goals are documented explicitly.

---

## 3. Supported Environments

Automenu targets the following environments:

- ESP32 via serial console
- ESP32 via Telnet
- macOS terminals
- Linux terminals
- FreeBSD terminals

All environments share the same core logic.
Only the IO layer differs.

---

## 4. High-Level Architecture

Automenu is composed of four strictly separated layers:

1. IO Abstraction Layer  
2. Core Engine  
3. Renderer  
4. Configuration Layer  

No layer may bypass another layer.

---

## 5. IO Abstraction Layer

The IO layer provides a minimal, platform-independent interface.

Responsibilities:

- character input
- character and string output
- screen clearing
- optional terminal capability detection

The core engine must not access platform-specific APIs directly.

---

## 6. Core Engine

The core engine is responsible for:

- menu navigation
- state handling
- menu stack management
- paging logic
- key handling
- action dispatching

The core engine does not perform rendering and does not access configuration files directly.

---

## 7. Menu Model

Menus are defined using a declarative menu model.

A menu consists of:

- a unique identifier
- a title
- optional descriptive text
- a list of menu entries

Each menu entry defines:

- a selection key
- a label
- a type (submenu, action, info)
- a target reference

Menus are generated dynamically from configuration data.

---

## 8. Navigation and State Model

Automenu uses a stack-based state model.

- the main menu is the base state
- submenus push new states onto the stack
- actions create temporary action states
- returning always pops the current state

Direct jumps between unrelated states are not allowed.

---

## 9. Paging

Menus exceeding the visible area are paged automatically.

Paging behavior:

- fixed visible area
- deterministic page size
- explicit navigation keys
- page indicators shown in the status line

Scrolling is logical, not visual.

---

## 10. Renderer

The renderer is responsible for all visual output.

Renderer responsibilities:

- layout and framing
- title rendering
- menu entry rendering
- selection highlighting
- status line rendering

The renderer operates on abstract roles, not raw ANSI codes.

---

## 11. Color and Display Handling

Color handling is profile-based.

Display profiles define:

- background color
- text color
- highlight color
- error color
- status color

Profiles may enforce colors or respect terminal defaults.

ASCII-only operation must always be supported.

---

## 12. Configuration System

Configuration is split into:

- menu configuration
- display configuration

Configuration files are human-readable and editable.

A factory default configuration must always exist and must never be modified.

---

## 13. Configuration Persistence and Backup

When saving configuration:

- the current configuration is backed up as `.bak`
- the new configuration is written atomically
- invalid configurations must not become active

Broken configurations are preserved for inspection.

---

## 14. Configuration via Menu

Configuration may be modified from within Automenu.

Allowed operations:

- value changes
- feature toggling
- profile selection
- saving or discarding changes

No access restrictions are enforced at menu level.

---

## 15. Startup Parameters and Recovery

Startup parameters always take precedence over configuration.

Mandatory recovery options include:

- factory reset
- safe mode
- direct configuration access
- forced display profile

Recovery mechanisms must not be disableable by configuration.

---

## 16. Error Handling

Automenu must fail gracefully.

Requirements:

- invalid input must not crash the system
- configuration errors must trigger fallback behavior
- IO failures must be detected and handled

The system must remain operable whenever possible.

---

## 17. Non-Goals

Automenu explicitly does not aim to provide:

- graphical user interfaces
- web-based frontends
- role-based access control
- network security features
- automatic remote updates

---

## 18. Versioning

This specification applies to the initial public versions of Automenu.

Changes to this document must be explicit and version-controlled.

