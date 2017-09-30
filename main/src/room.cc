#include <algorithm>
#include <cmath>
#include <iostream>

#include "controlled_movement.h"
#include "gun_component.h"
#include "input_component.h"
#include "light_component.h"
#include "movement.h"
#include "player_shooter.h"
#include "render_component.h"
#include "room.h"
#include "simple_renderer.h"
#include "transform_component.h"
#include "vector.h"

Room::Room(Engine& engine, EntityManager& entity_manager)
 : engine(engine),
   entity_manager(entity_manager) {
  // No implementation
}

void Room::init() {
  angle = 0;

  image = new Image("main/assets/sprites/non_convex.png");
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
    Light* light = new Light(colour, 400);
    lights.push_back(light);
  }
  lights.at(0)->setColour(first_colour);
  lights.at(1)->setColour(second_colour);

  // Creating entities and adding components in the new ECP model
  engine.addProcessor<ControlledMovement>();
  engine.addProcessor<PlayerShooter>();
  engine.addProcessor<Movement>();
  engine.addRenderer<SimpleRenderer>();
  Entity entity1 = entity_manager.createEntity();

  entity_manager.addComponent<InputComponent>(entity1);

  auto transform_component =
      entity_manager.addComponent<TransformComponent>(entity1);
  transform_component->transform.rotation.set(0, 1);

  auto light_component = entity_manager.addComponent<LightComponent>(entity1);
  SDL_Color colour = { 0xAA, 0x00, 0xAA, 0xFF };
  light_component->setParameters(colour, 400);

  auto render_component = entity_manager.addComponent<RenderComponent>(entity1);
  render_component->setImage("main/assets/sprites/non_convex.png");

  auto gun = entity_manager.addComponent<GunComponent>(entity1);
  Transform left;
  left.position.x = 40;
  left.position.y = 20;
  Transform right;
  right.position.x = 40;
  right.position.y = -20;
  gun->setNodes({ left, right });


  Entity entity2 = entity_manager.createEntity();
  transform_component =
      entity_manager.addComponent<TransformComponent>(entity2);
  transform_component->transform.position.x = -80;
  transform_component->transform.position.y = 40;
  render_component =
      entity_manager.addComponent<RenderComponent>(entity2);
  render_component->setImage("main/assets/sprites/non_convex.png");
  /*auto light_component = entity_manager.addComponent<LightComponent>(entity2);
  colour = { 0x44, 0x44, 0x00, 0xFF };
  light_component->setParameters(colour, 400);*/
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
  images.push_back(image);
  for (int i = 0; i < lights.size(); i++) {
    //lights.at(i)->setObjects(images);
  }

  Vector pos0 = Vector();
  pos0.x = 110 * cos(-angle * 1.1 * M_PI / 180);
  pos0.y = 110 * sin(-angle * 1.1 * M_PI / 180);
  lights.at(0)->setPosition(pos0);
  Vector pos1 = Vector();
  pos1.x = 110 * cos(angle * M_PI / 180);
  pos1.y = 110 * sin(angle * M_PI / 180);
  lights.at(1)->setPosition(pos1);
}

void Room::draw(GPU_Target* gpu_target) {
  for (int i = 0; i < lights.size(); i++) {
    //lights.at(i)->draw(gpu_target);
  }

  //highlight_shader->setLights(lights);

  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  //image->draw(gpu_target, 0, 0, angle * 0.01f);
  //glDisable(GL_BLEND);

  for (int i = 0; i < waves.size(); i++) {
    //waves.at(i)->draw(gpu_target);
  }
}

Room::~Room() {
  /*while (waves.size() > 0) {
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

  delete image;
  delete highlight_shader;*/
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
