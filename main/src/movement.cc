#include "kinetic_component.h"
#include "movement.h"
#include "transform_component.h"

Movement::Movement(EntityManager& entity_manager)
    : Processor(entity_manager) { }

Requirements Movement::chooseRequirements() const {
  Requirements requirements = {
    TransformComponent::getTypeId(),
    KineticComponent::getTypeId()
  };
  return requirements;
}

void Movement::update(long ms, const std::set<Entity>& entities) {
  for (const auto& entity : entities) {
    auto transform_component =
        entity_manager.getComponent<TransformComponent>(entity);
    auto kinetic_component =
        entity_manager.getComponent<KineticComponent>(entity);
    transform_component->transform.position += kinetic_component->velocity;
  }
}
