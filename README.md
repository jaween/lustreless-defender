Lustreless Defender
===================

Description
-----------
Defend your dimly-lit inhabitance against marauders by using a turret that fires
radiant projectiles.

This the source code for a submission to The Univesity of Adelaide CS Club's
Make a Game Competition.

**Team Name** Dining Philosophers
**Team Members** Jaween Ediriweera (a1647468)

All programming and game art by Jaween Ediriweera.

Controls
--------
Left and right arrow keys to turn the turret, space to fire.
Press enter to restart the game at the game over screen.

Dependencies
------------
 * SDL 2.0 - Displaying a window and keyboard input
 * SDL_gpu - Graphics dependency
 * OpenGL 3.0 or greater - Rendering
 * GLEW - GL runtime loader
 * Google Test - Unit tests
 * CMake - Compilation

Usage
-----
 1) Clone the SDL_Gpu GitHub repo by running:
    `git clone https://github.com/grimfang4/sdl-gpu.git sdl-gpu`
 2) Build and install SDL_Gpu by running:
    `cmake -G "Unix Makefiles"
     make
     sudo make install`
 3) Run the build script
    `./build.sh`
 4) Run the game
    `./bin/game`
