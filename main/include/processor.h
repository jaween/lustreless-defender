#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <set>

#include "component.h"
#include "entity_manager.h"
#include "type_utils.h"

class Processor {
 public:
  Processor(EntityManager& entity_manager);
  virtual Requirements chooseRequirements() const = 0;
  virtual void update(long ms, const std::set<Entity>& entities) = 0;

 protected:
  EntityManager& entity_manager;
};

#endif // PROCESSOR_H_
