#include <cmath>
#include <iostream>

#include "game.h"
#include "vector.h"

void Room::init() {
  // TODO(jaween): Implement
}

void Room::update() {
  // TODO(jaween): Implement
}

void Scene::draw(SDL_Renderer* renderer) {
  SDL_Rect screen_rect;
  screen_rect.x = 0;
  screen_rect.y = 0;
  screen_rect.w = 640;
  screen_rect.h = 640;

  SDL_SetRenderDrawColor(renderer, 0x10, 0x10, 0x10, 0xFF);
  SDL_RenderFillRect(
      renderer,
      &screen_rect);
}

void Scene::finish() {
  // TODO(jaween): Implement
}
