#include <iostream>

#include "collidable_component.h"
#include "enemy_component.h"
#include "enemy_spawner.h"
#include "kinetic_component.h"
#include "render_component.h"
#include "transform_component.h"

EnemySpawner::EnemySpawner(EntityManager& entity_manager)
    : Processor(entity_manager) {
  last_spawn = SDL_GetTicks();
  srand(0);
}

void EnemySpawner::update(long ms) {
  uint32_t time = SDL_GetTicks();
  if (time - last_spawn > 2000) {
    spawn();
    last_spawn = time;
  }
}

void EnemySpawner::setImageNames(std::vector<std::string> image_names) {
  this->image_names = image_names;
}

void EnemySpawner::spawn() {
  Entity entity = entity_manager.createEntity();

  // Random values
  // TODO: Pass screen dimensions to processors
  int index = rand() % image_names.size();
  int x = 240 - rand() % 480;
  float speed = 0.4f + (rand() % 5)/4.0f;

  auto transform_component =
      entity_manager.addComponent<TransformComponent>(entity);
  transform_component->transform.position.set(x, 240);

  auto render_component = entity_manager.addComponent<RenderComponent>(entity);
  render_component->setImage(image_names[index]);

  auto collidable_component =
      entity_manager.addComponent<CollidableComponent>(entity);
  collidable_component->setRadius(10);

  entity_manager.addComponent<EnemyComponent>(entity);

  auto kinetic_component =
      entity_manager.addComponent<KineticComponent>(entity);
  kinetic_component->velocity.set(0, -speed);
}
