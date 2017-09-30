#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <set>

#include "component.h"
#include "entity_manager.h"
#include "type_utils.h"

class Processor {
 public:
  Processor(EntityManager& entity_manager);
  Requirements getRequirements() const;
  Requirements getInterests() const;
  virtual void update(long ms) = 0;

 protected:
  EntityManager& entity_manager;
  Requirements requirements;
  Requirements interests;
};

#endif // PROCESSOR_H_
