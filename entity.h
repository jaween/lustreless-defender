#ifndef ENTITY_H_
#define ENTITY_H_

#include "SDL_gpu.h"

#include "shader.h"
#include "vector.h"

class Entity {
 public:
  Entity();
  Entity(Vector& position);
  virtual void update();
  virtual void draw(GPU_Target* gpu_target) = 0;
  void setPosition(Vector position);
  Vector getPosition();

 protected:
  Vector position;
  Shader* shader;
};

#endif // ENTITY_H_
