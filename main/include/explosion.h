#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "processor.h"

class Explosion : public Processor {
 public:
  Explosion(EntityManager& entity_manager);
  virtual void update(long ms);
};

#endif // EXPLOSION_H_
