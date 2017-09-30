#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "processor.h"

class Movement : public Processor {
 public:
  Movement(EntityManager& entity_manager);
  virtual void update(long ms);
  void setDimensions(int16_t width, int16_t height);

 private:
  int16_t width;
  int16_t height;
};

#endif // MOVEMENT_H_

