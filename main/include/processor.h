#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <set>
#include <vector>

#include "component.h"
#include "entity_manager.h"
#include "type_utils.h"

class Processor {
 public:
  Processor(EntityManager& entity_manager);
  Requirements getRequirements() const;
  Requirements getInterests() const;
  virtual void update(long ms) = 0;
  std::vector<Entity> getEntitiesToDelete();

 protected:
  EntityManager& entity_manager;
  Requirements requirements;
  Requirements interests;
  std::vector<Entity> entities_to_delete;
};

#endif // PROCESSOR_H_
