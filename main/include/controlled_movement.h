#ifndef CONTROLLED_MOVEMENT_H_
#define CONTROLLED_MOVEMENT_H_

#include "processor.h"

class ControlledMovement : public Processor {
 public:
  virtual Requirements chooseRequirements() const;
  virtual void update(long ms, const std::set<Entity>& entities);
};

#endif // CONTROLLED_MOVEMENT_H_

