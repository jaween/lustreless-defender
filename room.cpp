#include <cmath>
#include <iostream>

#include "room.h"
#include "vector.h"

void Room::init() {
  angle = 20;
}

void Room::update() {
  int current_waves_size = waves.size();

  for (int i = 0; i < current_waves_size; i++) {
    waves.at(i)->update();
  }

  if (fmod(angle, 20.0) == 0) {
    Vector origin(320, 240);
    Vector s(angle * M_PI / 180);
    Vector e((angle + 100) * M_PI / 180);
    waves.push_back(new Wave(origin, s, e, 0, waves));
  }

  for (int i = 0; i < waves.size(); i++) {
    if (waves.at(i)->tempShouldDestroy()) {
      waves.erase(waves.begin() + i);
      i--;
    }
  }

  angle += 1.0f;
}

void Room::draw(SDL_Renderer* renderer) {
  SDL_Rect screen_rect;
  screen_rect.x = 0;
  screen_rect.y = 0;
  screen_rect.w = 640;
  screen_rect.h = 640;

  SDL_SetRenderDrawColor(renderer, 0x10, 0x10, 0x10, 0xFF);
  SDL_RenderFillRect(
      renderer,
      &screen_rect);

  for (int i = 0; i < waves.size(); i++) {
    waves.at(i)->draw(renderer);
  }
}

void Room::finish() {
  while (waves.size() > 0) {
    Wave* wave = waves.at(waves.size() - 1);
    delete wave;
  }
  waves.clear();
}
