#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL_gpu.h"

#include "vector.h"

class Entity {
 public:
  Entity(Vector& position);
  virtual void update();
  virtual void draw(GPU_Target* gpu_target) = 0;

 protected:
  Vector position;
};

#endif // ENTITY_H_
