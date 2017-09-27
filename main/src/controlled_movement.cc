#include "controlled_movement.h"
#include "transform_component.h"

ControlledMovement::ControlledMovement(EntityManager& entity_manager)
    : Processor(entity_manager) {
  // No implementation
}

Requirements ControlledMovement::chooseRequirements() const {
  Requirements requirements = {
    TransformComponent::getTypeId()
  };
  return requirements;
}

void ControlledMovement::update(long ms, const std::set<Entity>& entities) {
  for (const auto& entity : entities) {
    std::vector<ComponentPtr> components = entity_manager.getComponents(entity);
    auto component = entity_manager.getComponent<TransformComponent>(entity);
    component->x++;
  }
}
