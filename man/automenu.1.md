% AUTOMENU(1)
% Marcel Sauder
% January 2026

# NAME

automenu – deterministic menu system for terminal and embedded environments

# SYNOPSIS

automenu menu.txt

# DESCRIPTION

Automenu is a small, deterministic menu framework designed for terminal-based and embedded systems.

It reads a menu definition from a configuration file and presents a navigable menu. Behaviour is fully defined by the menu configuration and compile-time policy. Rendering and input handling are adapter-specific.

Automenu is intended for use in interactive terminals, kiosk systems and embedded environments.

# ARGUMENTS

menu.txt  
Path to the menu configuration file.

If the configuration file is invalid, automenu exits with an error message indicating the line number and cause.

# TERMINAL CONTROLS

Arrow Up  
Move selection up.

Arrow Down  
Move selection down.

Enter  
Select the current menu item.

1–9  
Directly select a menu item by index.

.q  
Hidden hard exit. Only available if automenu was compiled with hard exit support enabled.

# MENU ITEM TYPES

action  
Triggers an action identified by an action ID. The action is handled by the action dispatcher.

submenu  
Enters another menu.

back  
Returns to the previous menu.

exit  
Requests program termination.

info  
Displays informational text without changing menu state.

# EXIT BEHAVIOUR

Automenu supports two exit mechanisms.

A soft exit is triggered by a menu item of type exit and is part of the menu configuration.

A hard exit is triggered by the secret key sequence .q and is handled entirely by the terminal adapter. Hard exit support is optional and controlled at compile time.

In kiosk or embedded builds, the hard exit is typically disabled.

# FILES

menu.txt  
Menu configuration file.

# DIAGNOSTICS

Configuration errors are reported with a descriptive message and line number.

Runtime errors are reported to standard error.

# RETURN VALUE

0  
Successful execution.

Non-zero  
Error during configuration loading or runtime.

# VERSION

Automenu v0.1.0

# AUTHOR

Marcel Sauder

# SEE ALSO

automenu configuration documentation

