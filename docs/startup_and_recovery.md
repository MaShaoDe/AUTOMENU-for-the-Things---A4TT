# Automenu for the Things – Startup and Recovery

## 1. Purpose

This document describes startup behavior, startup parameters and recovery mechanisms
for *Automenu for the Things*.

Its primary goal is to guarantee that the system is always recoverable,
even if configuration or display settings have been misconfigured.

## 2. Design Principle

Anything that can be broken from inside the menu must be repairable from outside the menu.

Startup and recovery mechanisms operate at a higher priority level than configuration
and cannot be disabled by configuration changes.

## 3. Startup Phases

Automenu startup follows a defined sequence:

1. process invocation or device boot
2. evaluation of startup parameters
3. loading of configuration files
4. validation of configuration
5. menu initialization and rendering

Recovery mechanisms may alter or interrupt this sequence.

## 4. Startup Parameters

Startup parameters are command-line options or equivalent boot triggers.

Rules:

* startup parameters always take precedence over configuration
* recovery-related parameters cannot be overridden or disabled
* parameters may be temporary or persistent, depending on behavior

On Unix systems, parameters are passed via command line arguments.
On embedded systems, equivalent triggers are used.

## 5. Mandatory Startup Parameters

The following startup parameters are mandatory for all platforms.

### 5.1 Factory Reset

`--default` or `--factory`

Behavior:

* current configuration is backed up
* factory default configuration is activated
* system starts using default settings

This operation modifies persistent state.

## 5.2 Reset with Confirmation

`--reset`

Behavior:

* prompts for confirmation if supported
* resets configuration to factory defaults
* restarts or reloads the system

This operation modifies persistent state.

## 5.3 Direct Configuration Access

`--config`

Behavior:

* bypasses normal startup menu
* opens configuration menu directly
* ignores whether configuration menus are visible in normal navigation

This parameter does not modify persistent state unless changes are saved.

## 5.4 Safe Mode

`--safe`

Behavior:

* forces ASCII-only rendering
* disables color and background enforcement
* limits features to core functionality
* ignores display configuration

Safe mode is intended for recovery and diagnostics.

## 5.5 Forced Display Profile

`--profile <name>`

Behavior:

* forces a specific display profile
* overrides display configuration temporarily
* may be combined with safe mode

This parameter does not modify persistent state unless explicitly saved.

## 6. Parameter Precedence

Precedence order:

1. startup parameters
2. validated configuration
3. factory defaults

Configuration values never override startup parameters.

## 7. Embedded System Triggers

On embedded systems, startup parameters may be triggered by:

* specific key presses during boot
* serial input at startup
* hardware buttons or jumpers
* detection of invalid or missing configuration

These triggers provide equivalent recovery paths.

## 8. Automatic Recovery

Automenu performs automatic recovery under certain conditions.

Examples:

* configuration file cannot be parsed
* configuration validation fails
* display configuration causes unreadable output

Automatic recovery behavior:

* faulty configuration is preserved and renamed
* factory defaults are loaded
* a clear status message is shown

Automatic recovery must never result in an endless loop.

## 9. Persistent vs Temporary Overrides

Startup parameters may be:

* temporary (active for the current session only)
* persistent (explicitly saved by the user)

Rules:

* recovery parameters are temporary by default
* persistent changes require explicit user action
* implicit persistence is not allowed

This avoids accidental permanent changes.

## 10. User Feedback During Recovery

During recovery operations, Automenu must:

* clearly indicate recovery mode
* explain which action was taken
* provide next steps where possible

Silent recovery without feedback is not allowed.

## 11. Failure Scenarios

Automenu must handle the following failure scenarios gracefully:

* missing configuration files
* corrupted configuration data
* unsupported terminal capabilities
* interrupted IO connections

In all cases, the system must attempt to remain usable.

## 12. Testing Recovery Paths

Recovery mechanisms must be testable.

Requirements:

* all startup parameters must be documented
* recovery paths must be deterministic
* automated or manual testing must be possible

Recovery behavior must not rely on undocumented side effects.

## 13. Summary

Startup and recovery mechanisms ensure that Automenu:

* cannot lock users out permanently
* remains usable after misconfiguration
* provides clear and predictable recovery paths

Recovery is a core feature, not an afterthought.

