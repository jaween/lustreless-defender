#include "kinetic_component.h"
#include "movement.h"
#include "transform_component.h"

Movement::Movement(EntityManager& entity_manager)
    : Processor(entity_manager) {
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
    transform_component->transform.position += kinetic_component->velocity;
  }
}
