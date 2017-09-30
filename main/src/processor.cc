#include "processor.h"

Processor::Processor(EntityManager& entity_manager)
 : entity_manager(entity_manager) { }

Requirements Processor::getRequirements() const {
  return requirements;
}

Requirements Processor::getInterests() const {
  return interests;
}
