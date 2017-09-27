#include <SDL2/SDL.h>

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
  const Uint8* key_states = SDL_GetKeyboardState(NULL);

  // Moves the entity using the arrow keys
  for (const auto& entity : entities) {
    std::vector<ComponentPtr> components = entity_manager.getComponents(entity);
    auto component = entity_manager.getComponent<TransformComponent>(entity);

    if (key_states[SDL_SCANCODE_LEFT]) {
      component->position.x--;
    }
    if (key_states[SDL_SCANCODE_UP]) {
      component->position.y++;
    }
    if (key_states[SDL_SCANCODE_RIGHT]) {
      component->position.x++;
    }
    if (key_states[SDL_SCANCODE_DOWN]) {
      component->position.y--;
    }
  }
}
