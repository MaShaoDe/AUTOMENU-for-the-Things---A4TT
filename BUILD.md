# Automenu for the Things

### by Marcel Sauder, 2026

Automenu is built without a build system. All builds are explicit and reproducible.

Development build with terminal adapter and hidden hard exit (.q enabled):

cc -DALLOW_HARD_EXIT -Iinclude \
src/core/core.c \
src/config_loader.c \
src/action_dispatcher.c \
src/terminal.c \
-o automenu

Kiosk or embedded build without hard exit:

cc -Iinclude \
src/core/core.c \
src/config_loader.c \
src/action_dispatcher.c \
src/terminal.c \
-o automenu

The difference between the two builds is purely a compile-time policy decision. The source tree is identical.

For embedded targets, the terminal adapter may be replaced. The core, configuration loader and action dispatcher remain unchanged.

This build description applies to Automenu v0.1.0.
