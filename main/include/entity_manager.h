#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <algorithm>
#include <cstdint>
#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "base_component.h"
#include "type_utils.h"

using ComponentsMap = std::unordered_map<ComponentId, ComponentPtr>;
using EntityComponentsMap = std::unordered_map<Entity, ComponentsMap>;
using Capabilities = std::set<ComponentId>;

class EntityManager {
 public:
  EntityManager();
  Entity createEntity();
  void deleteEntity(Entity entity);
  std::vector<Entity> getEntities();

  // TODO(jaween): Separate the implementation into a separate file!
  template<class T>
  std::shared_ptr<T> addComponent(Entity entity) {
    // Adds component to collection
    // TODO(jaween): Use (variadic?) arguments to construct Component
    ComponentPtr component = std::make_shared<T>();
    ComponentId id = T::getTypeId();
    entity_components_map[entity][id] = component;

    // Adds to this entity's capability collection
    Capabilities& capabilities = entity_capabilities[entity];
    capabilities.insert(T::getTypeId());

    // Tracks requirements met by an entity and enities which meet requirements
    Capabilities intersection;
    for (const auto& pair : entities_which_match_requirements) {
      Requirements requirements = pair.first;

      // Skips processors that already know that this entity matches it
      if (entities_which_match_requirements[requirements].find(entity) !=
          entities_which_match_requirements[requirements].end()) {
        continue;
      }

      // Checks if this entity's capability set matches the requirements
      intersection.clear();
      std::set_intersection(capabilities.begin(),
                            capabilities.end(),
                            requirements.begin(),
                            requirements.end(),
                            std::inserter(intersection, intersection.begin()));

      if (intersection == requirements) {
        entities_which_match_requirements[requirements].insert(entity);
        requirements_matched_by_entities[entity].insert(requirements);
      }
    }

    return std::static_pointer_cast<T>(component);
  }

  template<class T>
  void removeComponent(Entity entity) {
    // Removes the component from this entity
    entity_components_map[entity].erase(T::getTypeId());

    // The entity now has fewer capabilities
    entity_capabilities[entity].erase(T::getTypeId());

    // Removes requirements which no longer match this entity's capabilities
    std::multiset<Requirements> requirements_set =
        requirements_matched_by_entities[entity];
    for (const auto& r : requirements_set) {
      if (r.find(T::getTypeId()) != r.end()) {
        requirements_matched_by_entities[entity].erase(r);

        // Inversely, the entity no loger matches this requirements
        entities_which_match_requirements[r].erase(entity);
       }
    }
  }

  template<class T>
  std::shared_ptr<T> getComponent(Entity entity) {
    // Casts a BaseComponent into a derived template Component
    auto iter = entity_components_map.find(entity);
    if (iter == entity_components_map.end()) {
      return nullptr;
    }

    ComponentsMap map = entity_components_map[entity];
    std::shared_ptr<BaseComponent> component_ptr;
    if (map.find(T::getTypeId()) == map.end()) {
      return nullptr;
    }

    component_ptr = map[T::getTypeId()];
    return std::static_pointer_cast<T>(component_ptr);
  }

  std::vector<ComponentPtr> getComponents(Entity entity);
  std::set<Entity> getEntities(const Requirements& requirements);
  void addRequirements(const Requirements& requirements);
  void clear();

 private:
  uint64_t next_entity_id;
  std::set<Entity> entities;
  EntityComponentsMap entity_components_map;
  std::unordered_map<Requirements, std::set<Entity>, SetHasher>
      entities_which_match_requirements;
  std::unordered_map<Entity, Capabilities> entity_capabilities;
  std::unordered_map<Entity, std::multiset<Requirements>>
      requirements_matched_by_entities;
};

#endif // ENTITY_MANAGER_H_
