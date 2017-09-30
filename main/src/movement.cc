#include "collidable_component.h"
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

    float radius = 20;
    auto collidable_component =
        entity_manager.getComponent<CollidableComponent>(entity);
    if (collidable_component != nullptr) {
      radius = collidable_component->radius;
    }

    if (position.x < -width/2 - radius ||
        position.x >= width/2 + radius ||
        position.y < -height/2 - radius ||
        position.y >= height/2 + radius) {
      entity_manager.deleteEntity(entity);
    }
  }
}

void Movement::setDimensions(int16_t width, int16_t height) {
  this->width = width;
  this->height = height;
}
