#include <iostream>

#include "component.h"
#include "entity_manager.h"

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

std::set<Entity> EntityManager::getEntities(Requirements requirements) {
  return entities_which_match_requirements[requirements];
}

void EntityManager::addRequirements(Requirements requirements) {
  // TODO(jaween): How about processors already using this set of requirements?
  if (entities_which_match_requirements.count(requirements) > 0) {
    std::cerr << "PROCESSOR EXISTS" << std::endl;
  }

  // TODO(jaween): There already may be matching entities, add those!
  std::set<Entity> entities;
  entities_which_match_requirements[requirements] = entities;
}
