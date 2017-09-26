#ifndef ENTITY_OLD_H_
#define ENTITY_OLD_H_

#include "SDL_gpu.h"

#include "shader.h"
#include "vector.h"

class EntityOld {
 public:
  EntityOld();
  EntityOld(Vector& position);
  virtual void update();
  virtual void draw(GPU_Target* gpu_target) = 0;
  void setPosition(Vector position);
  Vector getPosition();

 protected:
  Vector position;
  Shader* shader;
};

#endif // ENTITY_OLD_H_
