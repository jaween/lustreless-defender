#include "explosion_component.h"
#include "explosion.h"
#include "light_component.h"

Explosion::Explosion(EntityManager& entity_manager)
    : Processor(entity_manager) {
  requirements = {
    ExplosionComponent::getTypeId(),
    LightComponent::getTypeId()
  };
}

void Explosion::update(long ms) {
  auto entities = entity_manager.getEntities(requirements);
  for (const auto& entity : entities) {
    auto explosion_component =
        entity_manager.getComponent<ExplosionComponent>(entity);
    explosion_component->remaining--;
    if (explosion_component->remaining <= 0) {
        entities_to_delete.push_back(entity);
    }
  }
}
