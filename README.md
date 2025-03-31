# Arcade: A Retro Gaming Platform

Arcade is a retro-style gaming platform written in C++ that dynamically loads both game and graphics libraries at runtime. With a modular and plug-and-play design, Arcade allows you to easily switch between different games and graphical interfaces.

## Features
- **Dynamic Libraries**: Load game and graphics libraries at runtime using `dlopen`, `dlsym`, and `dlclose` with a generic, uniform approach.
- **Multiple Graphics Libraries**: Supports nCurses, SDL2, and more (e.g., SFML, Allegro5, etc.).
- **Multiple Game Libraries**: Enjoy classic games like Snake, Pacman, Nibbler, and others.
- **Extensible Architecture**: Add new games or graphical interfaces without modifying the core logic.

## Usage
Launch Arcade by specifying the initial graphical library:
```bash
./arcade ./lib/arcade_ncurses.so
```

## When Running

When running, the platform will display:

- **Available game libraries** (from the `./lib/` directory).
- **Available graphical libraries** (from the `./lib/` directory).
- **Current scores.**
- A field to **enter your username.**

Key mappings allow you to:

- **Switch to the next graphics library.**
- **Change the game.**
- **Restart the game.**
- **Return to the menu.**
- **Exit the platform.**

---


### Buid - CMake

```bash
mkdir build && cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

or

```bash
./shell/cmpRelease.sh
```

## Error Handling

- All error messages are printed to standard error.
- The program exits with code **84** when an error occurs (e.g., invalid arguments or incompatible dynamic libraries).

## Documentation

For detailed documentation on the platform, including how to implement new graphics or game libraries, please refer to the documentation in the `./doc` directory.

## Collaborators

We have developed this project as part of the EPITECH curriculum. The contributors to this project are:
Our team: **eliott.tesnier@epitech.eu** - **nolan.papa@epitech.eu** - **noa.roussiere@epitech.eu**
Architecture group: **albane.merian@@epitech.eu** - **alban.roussee@epitech.eu** - **matisse.marsac@epitech.eu**
