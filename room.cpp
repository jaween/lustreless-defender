#include <algorithm>
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

  // Temporary wave creation for testing multiple angles
  if (fmod(angle, 40.0) == 0) {
    Vector origin(320, 240);
    Vector s(angle * M_PI / 180);
    Vector e((angle + 100) * M_PI / 180);
    waves.push_back(new Wave(origin, s, e, 0, waves, 0));
  }
  angle += 1.0f;

  // Deletes the waves that have marked themselves to be destroyed
  for (int i = 0; i < waves.size(); i++) {
    if (waves.at(i)->tempShouldDestroy()) {
      waves.erase(waves.begin() + i);
      i--;
    }
  }

  mergeWaves();
}

void Room::draw(GPU_Target* gpu_target) {
  SDL_Color color = { 0x00, 0x00, 0x00, 0xFF };
  GPU_ClearColor(gpu_target, color);

  for (int i = 0; i < waves.size(); i++) {
    waves.at(i)->draw(gpu_target);
  }
}

void Room::finish() {
  while (waves.size() > 0) {
    Wave* wave = waves.at(waves.size() - 1);
    delete wave;
  }
  waves.clear();
}

void Room::mergeWaves() {
  std::sort(waves.begin(), waves.end(), [](Wave* lhs, Wave* rhs) {
    return lhs->getOrigin() == rhs->getOrigin()
        ? lhs->getRadius() < rhs->getRadius()
        : lhs->getOrigin() < rhs->getOrigin();
  });

  //std::clog << "Before merging, there are " << waves.size() << " waves\n";
  //printWaves();

  Wave* previous = waves.size() > 0 ? waves.at(0) : NULL;
  for (int i = 1; i < waves.size(); i++) {
    Wave* wave = waves.at(i);
    float kMaxMergeAngle = 1.0f * M_PI / 180;
    bool concentric_and_coradial =
        wave->getOrigin() == previous->getOrigin()
        && wave->getRadius() == previous->getRadius();
    // TODO(jaween): Don't merge if the new arc would intersect any wall
    bool far_apart =
        wave->getEnd().angleBetween(previous->getStart()) > kMaxMergeAngle
        && previous->getEnd().angleBetween(wave->getStart()) > kMaxMergeAngle;
    if (concentric_and_coradial && !far_apart) {
      //std::clog << "  Merging " << i - 1 << " and " << i << "...\n";
      Vector new_start = wave->getStart().isClockWiseOf(previous->getStart())
          ? previous->getStart()
          : wave->getStart();
      Vector new_end = wave->getEnd().isClockWiseOf(previous->getEnd())
          ? wave->getEnd()
          : previous->getEnd();
      Vector new_origin = wave->getOrigin();

      // TODO(jaween): Reuse old waves rather than allocating a new one
      Wave* new_wave = new Wave(new_origin, new_start, new_end,
          wave->getRadius(), waves, 0);

      waves.erase(waves.begin() + i - 1);
      waves.erase(waves.begin() + i - 1);
      waves.insert(waves.begin() + i - 1, new_wave);

      delete previous;
      delete wave;

      previous = new_wave;
      i--;
    } else {
      previous = wave;
    }
  }

  std::clog << "  There are now " << waves.size() << " waves" << std::endl;
  std::clog << std::endl;
}

void Room::printWaves() {
  for (int i = 0; i < waves.size(); i++) {
    Wave wave = *waves.at(i);
    float start_deg = (wave.getStart().angle() * 180 / M_PI);
    float end_deg = (wave.getEnd().angle() * 180 / M_PI);
    std::clog << "  " << i << ") Origin:" << wave.getOrigin() << ", radius:"
        << wave.getRadius() << ", <" << start_deg << ", " << end_deg
        << ">(spread " << (end_deg - start_deg) << ")" << std::endl;
  }
}
