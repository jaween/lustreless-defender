#include "entity_manager.h"

#include "component.h"

EntityManager::EntityManager()
 : next_entity_id(0) { }

Entity EntityManager::createEntity() {
  Entity entity { next_entity_id++ };
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
