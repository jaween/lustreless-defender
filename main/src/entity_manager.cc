#include "entity_manager.h"

#include "component.h"

EntityManager::EntityManager()
 : next_id(0) { }

Entity EntityManager::createEntity() {
  Entity entity { next_id++ };
  entities.insert(entity);
  return entity;
}

void EntityManager::deleteEntity(Entity entity) {
  entities.erase(entity);
}

std::vector<Entity> EntityManager::getEntities() {
  std::vector<Entity> vector;
  std::copy(entities.begin(), entities.end(), std::back_inserter(vector));
  return vector;
}

void EntityManager::removeComponent(Entity entity,
    const ComponentPtr& component) {
  ComponentsMap& map = entity_components_map[entity];

  auto range = map.equal_range(component->typeId());

  for (auto iter = range.first; iter != range.second; ++iter) {
    if (iter->second == component) {
      map.erase(iter);
      break;
    }
  }
}
