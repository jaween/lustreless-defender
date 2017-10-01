#include <vector>
#include <iostream>

#include "bullet_component.h"
#include "collidable_component.h"
#include "collision_detector.h"
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

      // Destroy the other if only one is a bullet
      auto bullet_a = entity_manager.getComponent<BulletComponent>(a);
      auto bullet_b = entity_manager.getComponent<BulletComponent>(b);
      if ((bullet_a == nullptr && bullet_b != nullptr) ||
          (bullet_a != nullptr && bullet_b == nullptr)) {
        if ((position_a - position_b).length() < radius_a + radius_b) {
          entities_to_delete.push_back(a);
          entities_to_delete.push_back(b);
        }
      }
    }
  }
}


