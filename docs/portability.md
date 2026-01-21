# Automenu for the Things – Portability

## 1. Purpose

This document describes how *Automenu for the Things* achieves portability across different platforms and environments.

It explains platform differences, abstraction layers and design constraints that ensure identical behavior wherever possible.

## 2. Supported Platforms

Automenu is designed to run on the following classes of systems:

* embedded systems (ESP32)
* Unix-like operating systems

  * FreeBSD
  * Linux
  * macOS

All platforms share the same conceptual model and user experience.

## 3. Portability Goals

Primary portability goals are:

* identical menu behavior across platforms
* identical navigation and key handling
* identical configuration semantics
* minimal platform-specific code

Perfect visual identity is secondary to functional identity.

## 4. Core and Platform Layers

Automenu is structured into two major parts:

* platform-independent core
* platform-specific adapters

The core contains all logic related to:

* menu state handling
* configuration parsing
* action dispatching
* navigation and paging

Platform adapters are limited to input and output handling.

## 5. IO Abstraction

All platform differences are isolated in the IO abstraction layer.

Responsibilities of the IO layer:

* character input
* character output
* screen clearing
* basic terminal capability hints

The core engine never accesses platform APIs directly.

## 6. Unix Systems

On Unix-like systems, Automenu interacts with:

* standard input
* standard output
* standard error

Terminal behavior is controlled using conservative ANSI escape sequences.

Advanced terminal features are avoided to maximize compatibility.

## 7. macOS Specifics

macOS behaves largely like other Unix systems but has notable differences:

* different default installation prefixes
* Homebrew and MacPorts packaging conventions
* Apple Silicon architecture considerations

These differences affect build and installation only, not runtime behavior.

## 8. FreeBSD Specifics

FreeBSD emphasizes long-term stability and clear separation between base system and ports.

Automenu aligns with FreeBSD conventions:

* installation under `/usr/local`
* configuration under `/usr/local/etc`
* ports-friendly build process

No FreeBSD-specific logic exists in the core engine.

## 9. Linux Specifics

Linux distributions vary widely in packaging and filesystem layout.

Automenu avoids distribution-specific assumptions:

* no hardcoded paths
* no reliance on systemd or similar frameworks
* no distribution-specific build steps

Packaging is optional and external to the core project.

## 10. Embedded Systems (ESP32)

Embedded systems differ fundamentally from Unix hosts.

Key differences:

* no filesystem or limited filesystem
* constrained memory
* different startup model
* serial-based IO

Despite these differences, Automenu preserves the same menu logic and navigation model.

## 11. Configuration Portability

Configuration formats are designed to be portable.

Rules:

* same logical structure on all platforms
* platform-specific storage handled outside the core
* factory defaults always available

Configuration files may be embedded or compiled into firmware on embedded systems.

## 12. Display and Terminal Differences

Terminal capabilities vary between platforms and environments.

Automenu follows conservative rules:

* never assume color support
* never assume cursor positioning
* always support ASCII-only output

Display profiles abstract these differences.

## 13. Timing and Performance

Performance characteristics differ across platforms.

Design considerations:

* no tight polling loops
* minimal screen redraws
* predictable input handling

Embedded platforms may use simplified rendering strategies.

## 14. Testing Across Platforms

Portability requires continuous testing.

Recommended testing environments:

* serial console (embedded)
* SSH sessions
* local terminal emulators

Behavioral differences must be documented explicitly.

## 15. Non-Goals

Automenu does not aim to:

* abstract all platform differences
* provide a uniform filesystem interface
* hide hardware limitations

Portability is achieved through restraint, not abstraction excess.

## 16. Summary

Automenu achieves portability by:

* strict separation of core and platform code
* conservative terminal assumptions
* identical configuration semantics
* minimal platform-specific logic

Functional consistency is prioritized over cosmetic uniformity.

