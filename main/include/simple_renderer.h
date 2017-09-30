#ifndef SIMPLE_RENDERER_H_
#define SIMPLE_RENDERER_H_

#include <memory>

#include "highlight_shader.h"
#include "renderer.h"

class SimpleRenderer : public Renderer {
 public:
  SimpleRenderer(EntityManager& entity_manager);
  virtual void render(long ms, GPU_Target* gpu_target);

 private:
  std::shared_ptr<HighlightShader> shader;
};

#endif // SIMPLE_RENDERER_H_
