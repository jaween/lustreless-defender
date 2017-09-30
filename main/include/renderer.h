#ifndef RENDERER_H_
#define RENDERER_H_

#include "image.h"
#include "processor.h"

class Renderer : public Processor {
 public:
  Renderer(EntityManager& entity_manager);
  virtual void update(long ms);
  virtual void render(long ms, GPU_Target* gpu_target) = 0;
};

#endif // RENDERER_H_
