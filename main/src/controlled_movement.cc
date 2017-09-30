#include <SDL2/SDL.h>

#include "controlled_movement.h"
#include "input_component.h"
#include "transform_component.h"

ControlledMovement::ControlledMovement(EntityManager& entity_manager)
    : Processor(entity_manager) {
  requirements = {
    TransformComponent::getTypeId(),
    InputComponent::getTypeId()
  };
}

void ControlledMovement::update(long ms) {
  const uint8_t* key_states = SDL_GetKeyboardState(NULL);

  auto entities = entity_manager.getEntities(requirements);
  // Moves the entity using the arrow keys
  for (const auto& entity : entities) {
    auto component = entity_manager.getComponent<TransformComponent>(entity);

    if (key_states[SDL_SCANCODE_LEFT]) {
      component->transform.position.x--;
    }
    if (key_states[SDL_SCANCODE_UP]) {
      component->transform.position.y++;
    }
    if (key_states[SDL_SCANCODE_RIGHT]) {
      component->transform.position.x++;
    }
    if (key_states[SDL_SCANCODE_DOWN]) {
      component->transform.position.y--;
    }
  }
}
