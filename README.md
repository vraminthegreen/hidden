# Evil Eye: Units Defense Roguelite

Evil Eye is a units-based tower defense roguelite game developed in C++ using the Raylib library.

## Prerequisites

- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.16 or higher

### Linux Dependencies
To build the project on Linux, you will need to install the following dependencies for Raylib:
```bash
sudo apt-get update
sudo apt-get install -y build-essential git cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev xorg-dev
```

## Building the Project

This project uses CMake and `FetchContent` to automatically download and build Raylib, ensuring simple cross-platform builds.

1. Create a build directory and run CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

2. Compile the project:
   ```bash
   make -j$(nproc)
   ```

## Running the Game

After a successful build, you can run the game executable from the `build` directory:
```bash
./build/EvilEye (lub `open build/EvilEye.app` na macOS)
```

## How to Play

- **Preparation Phase:** Left-click on blue Power Nodes to place Crystals (costs Minerals). Press SPACE to start the wave.
- **Combat Phase:**
  - **Spawn Minions:** Left-click on gray path tiles within the purple power range to spawn minions (costs Minerals and Ki).
  - **Hand of Power:** Right-click within the power range to cast a lightning strike on enemies (costs Energy).
- **Rewards:** At the end of each wave, select a reward using the `1`, `2`, or `3` keys.

Defend the Eye from the invading adventurers!
