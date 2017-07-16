#include <algorithm>
#include <cmath>
#include <iostream>

#include "room.h"
#include "vector.h"

void Room::init() {
  angle = 20;

  background = new Image("assets/sprites/triangle.png");
  highlight_shader = new HighlightShader();

  unsigned int first = 0x3299CC;
  unsigned int second = 0xFF0000;
  SDL_Color first_colour = {
      (uint8_t) (first >> 16),
      (uint8_t) ((first << 16) >> 24),
      (uint8_t) ((first << 24) >> 24),
      (uint8_t) (255)
  };
  SDL_Color second_colour = {
      (uint8_t) (second >> 16),
      (uint8_t) ((second << 16) >> 24),
      (uint8_t) ((second << 24) >> 24),
      (uint8_t) (255)
  };

  light_count = 2;
  for (int i = 0; i < light_count; i++) {
    SDL_Color colour = { 1, 1, 1, 1 };
    Light* light = new Light(colour);
    lights.push_back(light);
  }
  lights.at(0)->setColour(first_colour);
  lights.at(1)->setColour(second_colour);
}

void Room::update() {
  int current_waves_size = waves.size();
  for (int i = 0; i < current_waves_size; i++) {
    //waves.at(i)->update();
  }

  // Temporary wave creation for testing multiple angles
  if (fmod(angle, 40.0) == 0) {
    Vector origin(320, 240);
    Vector s(angle * M_PI / 180);
    Vector e((angle + 100) * M_PI / 180);
    //waves.push_back(new Wave(origin, s, e, 0, waves, 0));
  }
  angle += 1.0f;

  // Deletes the waves that have marked themselves to be destroyed
  for (int i = 0; i < waves.size(); i++) {
    if (waves.at(i)->tempShouldDestroy()) {
      waves.erase(waves.begin() + i);
      i--;
    }
  }

  //mergeWaves();

  std::vector<Image*> images;
  images.push_back(background);
  for (int i = 0; i < lights.size(); i++) {
    lights.at(i)->setObjects(images);
  }

  Vector pos0 = Vector();
  pos0.x = 320 + 110 * cos(-angle * 1.1 * M_PI / 180);
  pos0.y = 240 + 110 * sin(-angle * 1.1 * M_PI / 180);
  lights.at(0)->setPosition(pos0);
  Vector pos1 = Vector();
  pos1.x = 320 + 110 * cos(angle * M_PI / 180);
  pos1.y = 240 + 110 * sin(angle * M_PI / 180);
  lights.at(1)->setPosition(pos1);
}

void Room::draw(GPU_Target* gpu_target) {
  SDL_Color color = { 0x00, 0x00, 0x00, 0xFF };
  GPU_ClearColor(gpu_target, color);

  for (int i = 0; i < lights.size(); i++) {
    lights.at(i)->draw(gpu_target);
  }

  highlight_shader->setLights(lights);
  background->draw(gpu_target, 320, 240, highlight_shader);

  for (int i = 0; i < waves.size(); i++) {
    //waves.at(i)->draw(gpu_target);
  }
}

void Room::finish() {
  while (waves.size() > 0) {
    Wave* wave = waves.at(waves.size() - 1);
    delete wave;
  }
  waves.clear();

  while (lights.size() > 0) {
    Light* light = lights.at(lights.size() - 1);
    std::clog << "Lights size is " << lights.size() << std::endl;
    delete light;
  }
  lights.clear();

  delete background;
  delete highlight_shader;
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
