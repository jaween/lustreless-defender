#include <algorithm>
#include <cmath>
#include <iostream>

#include "collidable_component.h"
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
  // Setup the processors and the renderers
  engine.addProcessor<ControlledMovement>();
  engine.addProcessor<PlayerShooter>();
  auto movement_processor = engine.addProcessor<Movement>();
  engine.addRenderer<SimpleRenderer>();
  movement_processor->setDimensions(engine.getWidth(), engine.getHeight());

  // Component assemblages
  createTurret();
  createBaseLights();
  createBackgroundElements();
  createMisc();
}

void Room::createTurret() {
  Entity turret = entity_manager.createEntity();

  auto render_component = entity_manager.addComponent<RenderComponent>(turret);
  render_component->setImage("main/assets/sprites/turret.png");

  auto transform_component =
      entity_manager.addComponent<TransformComponent>(turret);
  transform_component->transform.position.set(0,
      -engine.getHeight() / 2 + 40);
  transform_component->transform.rotation.set(0, 1);

  entity_manager.addComponent<InputComponent>(turret);

  auto collidable_component =
      entity_manager.addComponent<CollidableComponent>(turret);
  collidable_component->setRadius(75);

  auto gun = entity_manager.addComponent<GunComponent>(turret);
  Transform left;
  left.position.set(40, 20);
  Transform right;
  right.position.set(40, -20);
  gun->setNodes({ left, right });
}

void Room::createBaseLights() {
  const int diameter = engine.getWidth();

  // Left base light
  Entity left_light = entity_manager.createEntity();

  auto transform_component =
      entity_manager.addComponent<TransformComponent>(left_light);
  transform_component->transform.position.set(
      -engine.getWidth() / 2 + diameter / 5,
      -engine.getHeight() / 2 + diameter / 9);

  auto light_component =
      entity_manager.addComponent<LightComponent>(left_light);
  SDL_Color colour = { 0xAA, 0x00, 0xAA, 0xFF };
  light_component->setParameters(colour, diameter);

  // Right base light
  Entity right_light = entity_manager.createEntity();

  transform_component =
      entity_manager.addComponent<TransformComponent>(right_light);
  transform_component->transform.position.set(
      engine.getWidth() / 2 - diameter / 5,
      -engine.getHeight() / 2 + diameter / 9);

  light_component =
      entity_manager.addComponent<LightComponent>(right_light);
  colour = { 0xAA, 0x00, 0xAA, 0xFF };
  light_component->setParameters(colour, diameter);
}

void Room::createBackgroundElements() {
  Entity entity = entity_manager.createEntity();

  auto transform_component =
      entity_manager.addComponent<TransformComponent>(entity);
  transform_component->transform.position.set(0, 0);

  auto render_component =
      entity_manager.addComponent<RenderComponent>(entity);
  render_component->setImage("main/assets/sprites/background.png");
}

void Room::createMisc() {
  Entity entity = entity_manager.createEntity();

  auto transform_component =
      entity_manager.addComponent<TransformComponent>(entity);
  transform_component->transform.position.set(-80, 40);

  auto render_component =
      entity_manager.addComponent<RenderComponent>(entity);
  render_component->setImage("main/assets/sprites/non_convex.png");

  auto collidable_component =
      entity_manager.addComponent<CollidableComponent>(entity);
  collidable_component->setRadius(75);
}

void Room::update() {
  /*int current_waves_size = waves.size();
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
  lights.at(1)->setPosition(pos1);*/
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
