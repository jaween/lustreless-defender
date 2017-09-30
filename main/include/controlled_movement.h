#ifndef CONTROLLED_MOVEMENT_H_
#define CONTROLLED_MOVEMENT_H_

#include "processor.h"

class ControlledMovement : public Processor {
 public:
  ControlledMovement(EntityManager& entity_manager);
  virtual void update(long ms);
};

#endif // CONTROLLED_MOVEMENT_H_

