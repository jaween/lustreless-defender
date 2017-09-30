#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "processor.h"

class Movement : public Processor {
 public:
  Movement(EntityManager& entity_manager);
  virtual Requirements chooseRequirements() const;
  virtual void update(long ms, const std::set<Entity>& entities);
};

#endif // MOVEMENT_H_

