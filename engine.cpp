#include <iostream>

#include "engine.h"

Engine::Engine(const Room& room)
    : room(room) {
  std::clog << "Engine started" << std::endl;
}

void Engine::run() {
  if (!init()) {
    return;
  }

  room.init();

  bool keepRunning = true;
  while (keepRunning) {
    // Input handling
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0) {
      switch (event.type) {
        case SDL_QUIT:
          keepRunning = false;
          break;
      }
    }

    room.update();
    room.draw(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(10);
  }

  finish();
}

bool Engine::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed to initialise SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  int result = SDL_CreateWindowAndRenderer(
      kScreenWidth,
      kScreenHeight,
      0,
      &window,
      &renderer);

  if (result != 0) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void Engine::finish() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }

  if (window) {
    SDL_DestroyWindow(window);
  }

  SDL_Quit();

  std::clog << "Engine ended" << std::endl;
}
