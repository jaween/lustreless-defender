#include "SDL_gpu.h"

#include "simple_renderer.h"
#include "render_component.h"
#include "transform_component.h"

SimpleRenderer::SimpleRenderer(EntityManager& entity_manager)
    : Renderer(entity_manager) {
  // No implementation
}

Requirements SimpleRenderer::chooseRequirements() const {
  Requirements requirements = {
    TransformComponent::getTypeId(),
    RenderComponent::getTypeId()
  };
  return requirements;
}

void SimpleRenderer::update(long ms, const std::set<Entity>& entities) {
  // No implementation
}

void SimpleRenderer::render(long ms, const std::set<Entity>& entities,
                            GPU_Target* gpu_target) {
  for (const auto& entity : entities) {
    auto transform = entity_manager.getComponent<TransformComponent>(entity);
    auto render = entity_manager.getComponent<RenderComponent>(entity);
    render->getImage()->draw(gpu_target, transform->x, transform->y);
  }
}
