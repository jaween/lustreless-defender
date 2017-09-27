#ifndef RENDERER_H_
#define RENDERER_H_

#include "image.h"
#include "processor.h"

class Renderer : public Processor {
 public:
  Renderer(EntityManager& entity_manager);
  virtual Requirements chooseRequirements() const = 0;
  virtual void update(long ms, const std::set<Entity>& entities) = 0;
  virtual void render(long ms, const std::set<Entity>& entities,
      GPU_Target* gpu_target) = 0;
};

#endif // RENDERER_H_
