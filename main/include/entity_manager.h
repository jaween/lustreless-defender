#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <cstdint>
#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "component.h"

typedef uint64_t Entity;
typedef std::shared_ptr<Component> ComponentPtr;
typedef std::unordered_multimap<ComponentId, ComponentPtr> ComponentsMap;
typedef std::unordered_map<Entity, ComponentsMap> EntityComponentsMap;

class EntityManager {
 public:
  EntityManager();
  Entity createEntity();
  void deleteEntity(Entity entity);
  std::vector<Entity> getEntities();

  // TODO(jaween): Separate the implementation into a separate file!
  template<class T>
  void addComponent(Entity entity) {
    ComponentId id = Component::getTypeId<T>();
    ComponentPtr ptr = std::shared_ptr<T>(new T);
    ComponentsMap& map = entity_components_map[entity];
    map.insert(std::pair<ComponentId, ComponentPtr>(id, ptr));
  }

  // TODO(jaween): Separate the implementation into a separate file!
  template<class T>
  std::vector<ComponentPtr> getComponents(Entity entity) {
    ComponentsMap map = entity_components_map[entity];
    std::vector<ComponentPtr> output;

    // TODO(jaween): Is there a better wap to do this?
    for (const auto& pair : map) {
      output.push_back(pair.second);
    }
    return output;
  }

 private:
  uint64_t next_id;
  std::set<Entity> entities;
  EntityComponentsMap entity_components_map;
};

#endif // ENTITY_MANAGER_H_
