#ifndef SIMPLE_RENDERER_H_
#define SIMPLE_RENDERER_H_

#include "renderer.h"

class SimpleRenderer : public Renderer {
 public:
  SimpleRenderer(EntityManager& entity_manager);
  virtual Requirements chooseRequirements() const;
  virtual void update(long ms, const std::set<Entity>& entities);
  virtual void render(long ms, const std::set<Entity>& entities,
      GPU_Target* gpu_target);
};

#endif // SIMPLE_RENDERER_H_
