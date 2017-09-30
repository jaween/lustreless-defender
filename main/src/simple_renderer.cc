#include "SDL_gpu.h"
#include <cmath>
#include <memory>
#include <unordered_map>

#include "image.h"
#include "light_component.h"
#include "simple_renderer.h"
#include "render_component.h"
#include "transform_component.h"
#include "transform.h"
#include "vector.h"

SimpleRenderer::SimpleRenderer(EntityManager& entity_manager)
    : Renderer(entity_manager) {
  requirements = {
    TransformComponent::getTypeId(),
    LightComponent::getTypeId()
  };

  interests = {
    TransformComponent::getTypeId(),
    RenderComponent::getTypeId()
    // CollidableComponent::getTypeId()
  };
}

void SimpleRenderer::render(long ms, GPU_Target* gpu_target) {
  // Prepares all of the lightable objects and draws them
  auto lightables = entity_manager.getEntities(interests);
  std::unordered_map<Transform, std::shared_ptr<Image>> objects;
  for (const auto& entity : lightables) {
    auto transform = entity_manager.getComponent<TransformComponent>(entity);
    auto render = entity_manager.getComponent<RenderComponent>(entity);
    objects[transform->transform] = render->getImage();
    render->getImage()->draw(
        gpu_target,
        transform->transform.position.x,
        transform->transform.position.y,
        transform->transform.rotation.angle());
  }

  // Draws the lights
  auto lights = entity_manager.getEntities(requirements);
  for (const auto& entity : lights) {
    auto transform = entity_manager.getComponent<TransformComponent>(entity);
    auto light = entity_manager.getComponent<LightComponent>(entity);
    light->light->draw(gpu_target,
                       transform->transform.position,
                       objects);
  }
}
