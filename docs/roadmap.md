# Automenu for the Things – Roadmap

## 1. Purpose

This document outlines the planned development roadmap for *Automenu for the Things*.

The roadmap provides orientation, not promises. It describes intended directions and priorities
while explicitly allowing for change based on practical experience.

## 2. Roadmap Philosophy

Automenu favors stability and clarity over rapid feature growth.

Roadmap principles:

* small, incremental steps
* working software over speculative features
* backward compatibility whenever possible
* explicit non-goals

Features are added only when they clearly support the core concept.

## 3. Versioning Strategy

Automenu follows a simple versioning model:

* major versions indicate architectural changes
* minor versions add functionality without breaking behavior
* patch versions fix bugs and documentation issues

Early versions prioritize correctness and clarity over completeness.

## 4. Phase 0 – Documentation and Concept Stabilization

Status: complete

Goals:

* establish core concept
* define architecture and design principles
* document configuration, display and recovery behavior
* create a stable documentation base

This phase results in a clear and frozen conceptual foundation.

## 5. Phase 1 – Core Engine Prototype

Goals:

* implement minimal core engine
* basic menu rendering
* stack-based navigation
* static menu configuration loading
* ASCII-only output

Target outcome:

* usable prototype
* serial and local terminal operation

## 6. Phase 2 – Configuration and Persistence

Goals:

* full menu configuration parsing
* display configuration support
* configuration backup and restore
* factory default handling
* startup parameter parsing

Target outcome:

* recoverable and configurable system

## 7. Phase 3 – Display Profiles and Color Handling

Goals:

* implement display profiles
* role-based rendering
* optional color enforcement
* ASCII fallback verification

Target outcome:

* consistent appearance across platforms

## 8. Phase 4 – Platform Adapters

Goals:

* Unix IO adapter refinement
* serial adapter for embedded systems
* Telnet-based IO adapter
* platform-specific build integration

Target outcome:

* identical behavior across supported platforms

## 9. Phase 5 – Packaging and Distribution

Goals:

* FreeBSD port
* Homebrew formula
* MacPorts port
* installation documentation validation

Target outcome:

* easy installation on major platforms

## 10. Phase 6 – Man Pages and Reference Completion

Goals:

* write and refine all man pages
* ensure consistency with behavior
* validate examples and options

Target outcome:

* complete reference documentation

## 11. Phase 7 – Hardening and Testing

Goals:

* error handling improvements
* robustness under invalid input
* recovery path testing
* cross-platform testing

Target outcome:

* stable and predictable behavior

## 12. Deferred and Optional Topics

Explicitly deferred topics include:

* graphical user interfaces
* web-based configuration
* scripting languages
* plugin systems
* remote management frameworks

These may be explored in separate projects if needed.

## 13. Review and Adjustment

The roadmap is reviewed periodically.

Adjustments may be made based on:

* real-world usage
* platform constraints
* maintenance effort

Changes are documented transparently.

## 14. Summary

The Automenu roadmap emphasizes:

* clarity before complexity
* stability before features
* documentation as a foundation

Progress is measured by reliability, not feature count.

