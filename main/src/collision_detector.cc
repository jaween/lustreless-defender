#include <vector>

#include "bullet_component.h"
#include "collidable_component.h"
#include "collision_detector.h"
#include "enemy_component.h"
#include "explosion_component.h"
#include "game_over_component.h"
#include "light_component.h"
#include "player_component.h"
#include "transform_component.h"

CollisionDetector::CollisionDetector(EntityManager& entity_manager)
    : Processor(entity_manager) {
  requirements = {
    TransformComponent::getTypeId(),
    CollidableComponent::getTypeId()
  };
}

void CollisionDetector::update(long ms) {
  auto entities = entity_manager.getEntities(requirements);

  std::vector<Entity> list;
  for (const auto& entity : entities) {
    list.push_back(entity);
  }

  // TODO(jaween): Use quad-tree to cut down on this n^2 collision algorithm
  // This is horrible
  for (unsigned int i = 0; i < list.size(); i++) {
    for (unsigned int j = i + 1; j < list.size(); j++) {
      Entity a = list[i];
      Entity b = list[j];
      auto transform_a = entity_manager.getComponent<TransformComponent>(a);
      auto transform_b = entity_manager.getComponent<TransformComponent>(b);
      auto position_a = transform_a->transform.position;
      auto position_b = transform_b->transform.position;
      auto radius_a =
          entity_manager.getComponent<CollidableComponent>(a)->radius;
      auto radius_b =
          entity_manager.getComponent<CollidableComponent>(b)->radius;

      if ((position_a - position_b).length() < radius_a + radius_b) {
        // Enemy and bullet collisions. Enemy and player collisions.
        auto bullet_a = entity_manager.getComponent<BulletComponent>(a);
        auto bullet_b = entity_manager.getComponent<BulletComponent>(b);
        auto enemy_a = entity_manager.getComponent<EnemyComponent>(a);
        auto enemy_b = entity_manager.getComponent<EnemyComponent>(b);
        auto player_a = entity_manager.getComponent<PlayerComponent>(a);
        auto player_b = entity_manager.getComponent<PlayerComponent>(b);
        if ((bullet_a != nullptr && enemy_b != nullptr) ||
            (bullet_b != nullptr && enemy_a != nullptr)) {
          entities_to_delete.push_back(a);
          entities_to_delete.push_back(b);

          auto explosion = entity_manager.createEntity();
          auto transform =
              entity_manager.addComponent<TransformComponent>(explosion);
          auto explosion_component =
              entity_manager.addComponent<ExplosionComponent>(explosion);
          explosion_component->remaining = 10;
          transform->transform.position = 0.5 * (position_a + position_b);
          auto light = entity_manager.addComponent<LightComponent>(explosion);
          SDL_Color colour = { 0xFF, 0xFF, 0xFF, 0xFF };
          light->setParameters(colour, 300);
        } else if ((enemy_a != nullptr && player_b != nullptr) ||
                   (enemy_b != nullptr && player_a != nullptr)) {
          auto game_over = entity_manager.createEntity();
          entity_manager.addComponent<GameOverComponent>(game_over);
        }
      }
    }
  }
}


