#include "controlled_movement.h"
#include "transform_component.h"

Requirements ControlledMovement::chooseRequirements() const {
  Requirements requirements = {
    TransformComponent::getTypeId()
  };
  return requirements;
}

void ControlledMovement::update(long ms, const std::set<Entity>& entities) {

}
