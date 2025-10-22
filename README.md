# Snake Clone

A classic Snake game implementation using C++ and Raylib.

<img width="778" height="803" alt="Snake gameplay screenshot" src="https://github.com/user-attachments/assets/553a4fc7-498a-43b0-9049-66937634d7d4" />

## Features

- Classic Snake gameplay mechanics
- Smooth movement and collision detection
- Score tracking
- Background music and sound effects
- Clean, modular C++ codebase

## Controls

- **WASD** or **Arrow Keys**: Move the snake
- Press any movement key to start the game
- **ESC**: Close the game

## Building

### Prerequisites

- C++ compiler with C++17 support (clang++ or g++)
- Raylib library
- pkg-config

### Compile

```bash
make
```

### Run

```bash
make run
```

### Clean

```bash
make clean
```

## Project Structure

```
Snake/
├── src/              # Source files
│   ├── main.cpp      # Entry point and game loop
│   ├── Game.cpp      # Main game logic and state
│   ├── Snake.cpp     # Snake entity
│   ├── Food.cpp      # Food entity
│   └── Global.cpp    # Global utilities and constants
├── include/          # Header files
│   ├── Game.hpp
│   ├── Snake.hpp
│   ├── Food.hpp
│   └── Global.hpp
├── Assets/           # Game assets
│   ├── Graphics/
│   │   └── Sprites/
│   └── Sounds/
│       ├── Music/
│       └── SFX/
├── Makefile          # Build configuration
└── README.md         # This file
```

## Architecture

The codebase is organized into separate, decoupled classes:

- **Game**: Manages game state, collision detection, and game loop
- **Snake**: Handles snake movement, rendering, and state
- **Food**: Manages food spawning and rendering
- **Global**: Shared utilities and timing functions

Each class has minimal dependencies and can be easily extended or modified.

## Credits

- **Developer**: Navi
- **Music**: "Breaking News" by SAKUMAMATATA
- **Death Sound**: From Galaga
- **Framework**: Raylib

## License

Feel free to use this code for learning purposes or as a base for your own projects.
