#include "processor.h"

Processor::Processor(EntityManager& entity_manager)
 : entity_manager(entity_manager) { }

Requirements Processor::getRequirements() const {
  return requirements;
}

Requirements Processor::getInterests() const {
  return interests;
}

std::vector<Entity> Processor::getEntitiesToDelete() {
  std::vector<Entity> temp = entities_to_delete;
  entities_to_delete.clear();
  return temp;
}
