#include <iostream>

#include "engine.h"

Engine::Engine() {
  std::clog << "Engine started" << std::endl;
}

void Engine::run() {
  if (!init()) {
    return;
  }

  bool keepRunning = true;
  while (keepRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        keepRunning = false;
      }
    }

    update();
    draw();

    SDL_Delay(10);
  }
  
  finish();
}

bool Engine::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed to initialise SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow(
      "Diffraction",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      kScreenWidth,
      kScreenHeight,
      SDL_WINDOW_SHOWN);
      
  if (window == NULL) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  }
  
  screen_surface = SDL_GetWindowSurface(window);

  return true;
}

void Engine::update() {
  // No implementation
}

void Engine::draw() {
  SDL_FillRect(
      screen_surface,
      NULL,
      SDL_MapRGB(screen_surface->format, 0xFF, 0x00, 0xFF));

  SDL_UpdateWindowSurface(window);
}

void Engine::finish() {
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::clog << "Engine ended" << std::endl;
}
