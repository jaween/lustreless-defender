#ifndef COLLISION_DETECTOR_H_
#define COLLISION_DETECTOR_H_

#include "processor.h"

class CollisionDetector : public Processor {
 public:
  CollisionDetector(EntityManager& entity_manager);
  virtual void update(long ms);
};

#endif // COLLISION_DETECTOR_H_

