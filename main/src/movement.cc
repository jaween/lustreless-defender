#include "collidable_component.h"
#include "enemy_component.h"
#include "game_over_component.h"
#include "kinetic_component.h"
#include "movement.h"
#include "transform_component.h"

Movement::Movement(EntityManager& entity_manager)
    : Processor(entity_manager),
      width(0),
      height(0) {
  requirements = {
    TransformComponent::getTypeId(),
    KineticComponent::getTypeId()
  };
}

void Movement::update(long ms) {
  auto entities = entity_manager.getEntities(requirements);

  for (const auto& entity : entities) {
    auto transform_component =
        entity_manager.getComponent<TransformComponent>(entity);
    auto kinetic_component =
        entity_manager.getComponent<KineticComponent>(entity);
    Vector& position = transform_component->transform.position;
    position += kinetic_component->velocity;

    // Destroys objects when they're outside of the screen
    float radius = 20;
    auto collidable_component =
        entity_manager.getComponent<CollidableComponent>(entity);
    if (collidable_component != nullptr) {
      radius = collidable_component->radius;
    }

    if (position.x < -width/2 - radius * 2 ||
        position.x >= width/2 + radius * 2 ||
        position.y < -height/2 - radius * 2 ||
        position.y >= height/2 + radius * 2) {
      entity_manager.deleteEntity(entity);
    }

    auto enemy_component = entity_manager.getComponent<EnemyComponent>(entity);
    if (enemy_component != nullptr) {
      if (position.y < -height/2 + 50) {
        auto game_over = entity_manager.createEntity();
        entity_manager.addComponent<GameOverComponent>(game_over);
      }
    }
  }
}

void Movement::setDimensions(int16_t width, int16_t height) {
  this->width = width;
  this->height = height;
}
