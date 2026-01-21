# Automenu for the Things – Man Pages

## 1. Purpose

This document describes the manual pages provided by *Automenu for the Things*.

Man pages are considered first-class documentation and are intended to provide concise,
accurate reference information for users and administrators.

---

## 2. General Principles

Man pages follow traditional Unix conventions.

Design principles:

* concise and factual
* no marketing language
* suitable for offline use
* consistent across platforms

Man pages complement the Markdown documentation but do not replace it.

---

## 3. Overview of Provided Man Pages

Automenu provides multiple manual pages, each with a clearly defined scope.

Planned man pages include:

* `automenu(1)` – main executable and runtime behavior
* `automenu.conf(5)` – menu configuration file format
* `automenu-display.conf(5)` – display configuration file format

Additional man pages may be added in the future if justified.

---

## 4. automenu(1)

### 4.1 Purpose

The `automenu(1)` man page documents the main Automenu executable.

It describes:

* invocation syntax
* command-line options
* startup and recovery parameters
* runtime behavior

---

### 4.2 Content Outline

The `automenu(1)` man page should include the following sections:

* NAME
* SYNOPSIS
* DESCRIPTION
* OPTIONS
* STARTUP AND RECOVERY
* CONFIGURATION FILES
* EXIT STATUS
* ENVIRONMENT
* FILES
* EXAMPLES
* SEE ALSO

---

## 5. automenu.conf(5)

### 5.1 Purpose

The `automenu.conf(5)` man page documents the menu configuration file format.

It serves as a reference for:

* configuration structure
* supported keys and values
* default behavior
* validation rules

---

### 5.2 Content Outline

The `automenu.conf(5)` man page should include:

* NAME
* DESCRIPTION
* FILE FORMAT
* MENU DEFINITIONS
* MENU ENTRIES
* ACTION TYPES
* COMMENTS
* EXAMPLES
* SEE ALSO

---

## 6. automenu-display.conf(5)

### 6.1 Purpose

The `automenu-display.conf(5)` man page documents display and rendering configuration.

It focuses on:

* display profiles
* color roles
* background enforcement
* fallback behavior

---

### 6.2 Content Outline

The `automenu-display.conf(5)` man page should include:

* NAME
* DESCRIPTION
* FILE FORMAT
* DISPLAY PROFILES
* COLOR ROLES
* ASCII FALLBACK
* VALIDATION
* EXAMPLES
* SEE ALSO

---

## 7. Installation of Man Pages

Man pages are installed as part of the standard installation process.

Default installation paths:

* `/usr/local/share/man/man1/`
* `/usr/local/share/man/man5/`

Paths may vary depending on the platform or packaging system.

---

## 8. Maintenance and Versioning

Man pages must be kept in sync with:

* the Automenu version
* the configuration format
* startup and recovery behavior

Changes to behavior require corresponding man page updates.

---

## 9. Relationship to Other Documentation

Man pages provide reference-level documentation.

They intentionally avoid:

* design rationale
* extended tutorials
* conceptual explanations

Such content belongs in the Markdown documentation under `docs/`.

---

## 10. Summary

Automenu man pages provide:

* authoritative command reference
* offline-accessible documentation
* stable and concise descriptions

They are a core part of the project, not an optional add-on.

