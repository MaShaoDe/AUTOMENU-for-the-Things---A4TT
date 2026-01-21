# Automenu for the Things – Build and Install

## 1. Purpose

This document describes how to build and install *Automenu for the Things* on supported platforms.

The focus is on simple, transparent and reproducible builds, following classic Unix conventions.

## 2. General Build Philosophy

Automenu is designed as a small, source-based tool.

Principles:

* no complex build systems
* no hidden code generation
* no mandatory external frameworks
* standard C toolchains
* explicit install locations

The same source tree is used across platforms.

## 3. Build Requirements

### 3.1 Common Requirements

All Unix-like systems require:

* a C compiler (clang or gcc)
* make
* standard C library
* POSIX-compatible environment

Optional:

* ncurses (only if explicitly enabled)
* pkg-config (for optional dependency detection)

### 3.2 Supported Toolchains

Automenu is intended to build with:

* clang (preferred)
* gcc

No compiler-specific extensions are required.

## 4. Source Tree Layout

Typical layout:

```
automenu/
├── src/
├── include/
├── docs/
├── examples/
├── Makefile
└── README.md
```

The top-level Makefile is the primary build entry point.

## 5. Building on Unix Systems

### 5.1 Default Build

To build Automenu from source:

```
make
```

This produces the `automenu` binary in the build directory.

### 5.2 Clean Build

To remove build artifacts:

```
make clean
```

## 6. Installation

### 6.1 Standard Installation

To install Automenu system-wide:

```
sudo make install
```

Default installation paths:

* binary: `/usr/local/bin/automenu`
* configuration: `/usr/local/etc/automenu/`
* man pages: `/usr/local/share/man/`

Installation paths may be overridden using standard make variables.

### 6.2 DESTDIR Installation

For packaging or staging:

```
make install DESTDIR=/path/to/stage
```

This is used by package managers and ports systems.

## 7. FreeBSD

### 7.1 FreeBSD Ports

Automenu is designed to be packaged as a FreeBSD port.

Characteristics:

* source-based build
* uses the standard Ports framework
* no bundled dependencies

Typical port files:

* `Makefile`
* `distinfo`
* `pkg-descr`
* optional `pkg-plist`

The port invokes the project Makefile and installs files using the standard FreeBSD layout.

### 7.2 Configuration Files on FreeBSD

Recommended locations:

* `/usr/local/etc/automenu/menu.conf`
* `/usr/local/etc/automenu/display.conf`

Factory default configuration files are shipped separately and are never overwritten during upgrades.

## 8. macOS

### 8.1 Homebrew

Automenu can be installed via Homebrew using a custom formula.

The formula:

* fetches the source code
* builds using make
* installs binaries and man pages
* installs default configuration files if not already present

This is the preferred installation method on macOS.

### 8.2 MacPorts

Automenu can also be packaged as a MacPorts port.

The MacPorts build process closely resembles FreeBSD Ports and can reuse much of the same structure.

### 8.3 Manual Build on macOS

For manual builds:

```
make
sudo make install
```

On Apple Silicon systems, installation paths such as `/opt/homebrew` may be used instead of `/usr/local`.

## 9. Linux

On Linux systems, Automenu is built and installed using the same process:

```
make
sudo make install
```

Distribution-specific packaging is optional and out of scope for the initial project phase.

## 10. Embedded Builds

Embedded targets such as ESP32 use a separate build process.

Characteristics:

* cross-compilation
* platform-specific toolchains
* different IO backends
* no system-wide installation

Embedded build instructions are documented separately.

## 11. Optional Features

Optional features may be enabled or disabled at build time.

Examples:

* color support
* ncurses integration
* debug logging

Optional features must be explicit and documented.

## 12. Man Pages

Man pages are installed as part of the standard installation.

Planned man pages include:

* `automenu(1)`
* `automenu.conf(5)`
* `automenu-display.conf(5)`

Man pages are considered part of the core documentation.

## 13. Summary

Automenu follows a traditional Unix build and install model:

* simple make-based builds
* transparent installation
* clean separation between build and runtime
* compatibility with ports and package systems

Build simplicity is a core design goal.

