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

typedef uint64_t Entity;
using ComponentPtr = std::shared_ptr<BaseComponent>;
using ComponentsMap = std::unordered_multimap<ComponentId, ComponentPtr>;
using EntityComponentsMap = std::unordered_map<Entity, ComponentsMap>;

class EntityManager {
 public:
  EntityManager();
  Entity createEntity();
  void deleteEntity(Entity entity);
  std::vector<Entity> getEntities();

  // TODO(jaween): Separate the implementation into a separate file!
  template<class T>
  void addComponent(Entity entity) {
    ComponentPtr component = std::shared_ptr<T>(new T);
    ComponentId id = T::getTypeId();
    ComponentsMap& map = entity_components_map[entity];
    map.insert(std::pair<ComponentId, ComponentPtr>(id, component));
  }

  void removeComponent(Entity entity, const ComponentPtr& component);

  // TODO(jaween): Separate the implementation into a separate file!
  template<class T>
  std::vector<ComponentPtr> getComponents(Entity entity) {
    ComponentsMap map = entity_components_map[entity];

    std::vector<ComponentPtr> output;
    std::transform(map.begin(), map.end(), std::back_inserter(output),
        [](std::pair<ComponentId, ComponentPtr> pair) {
          return pair.second;
        });
    return output;
  }

 private:
  uint64_t next_id;
  std::set<Entity> entities;
  EntityComponentsMap entity_components_map;
};

#endif // ENTITY_MANAGER_H_
