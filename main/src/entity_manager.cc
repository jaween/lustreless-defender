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
  entity_components_map.erase(entity);
  entity_capabilities.erase(entity);

  for (auto requirement : requirements_matched_by_entities[entity]) {
    entities_which_match_requirements[requirement].erase(entity);
  }
  requirements_matched_by_entities.erase(entity);
}

std::vector<Entity> EntityManager::getEntities() {
  std::vector<Entity> vector;
  std::copy(entities.begin(), entities.end(), std::back_inserter(vector));
  return vector;
}

std::vector<ComponentPtr> EntityManager::getComponents(Entity entity) {
  std::vector<ComponentPtr> output;
  auto iter = entity_components_map.find(entity);
  if (iter == entity_components_map.end()) {
    return output;
  }
  ComponentsMap map = iter->second;

  std::transform(map.begin(), map.end(), std::back_inserter(output),
      [](std::pair<ComponentId, ComponentPtr> pair) {
        return pair.second;
      });
  return output;
}

std::set<Entity> EntityManager::getEntities(const Requirements& requirements) {
  return entities_which_match_requirements[requirements];
}

void EntityManager::addRequirements(const Requirements& requirements) {
  // TODO(jaween): How about processors already using this set of requirements?
  if (entities_which_match_requirements.count(requirements) > 0) {
    std::cerr << "PROCESSOR WITH REQUIREMENTS EXISTS" << std::endl;
  }

  // TODO(jaween): There already may be matching entities, add those!
  std::set<Entity> entities;
  entities_which_match_requirements[requirements] = entities;
}

void EntityManager::clear() {
  next_entity_id = 0;
  entities.clear();
  entity_components_map.clear();
  entities_which_match_requirements.clear();
  entity_capabilities.clear();
  requirements_matched_by_entities.clear();
}
