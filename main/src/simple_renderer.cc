#include "SDL_gpu.h"
#include <cmath>
#include <memory>
#include <vector>
#include <iostream>
#include "collidable_component.h"
#include "image.h"
#include "light_component.h"
#include "simple_renderer.h"
#include "render_component.h"
#include "transform_component.h"
#include "transform.h"
#include "vector.h"

SimpleRenderer::SimpleRenderer(EntityManager& entity_manager)
    : Renderer(entity_manager) {
  // Lights
  requirements = {
    TransformComponent::getTypeId(),
    LightComponent::getTypeId()
  };

  // Lightable objects
  interests = {
    TransformComponent::getTypeId(),
    RenderComponent::getTypeId()
  };

  shader = std::shared_ptr<HighlightShader>(new HighlightShader);
}

void SimpleRenderer::render(long ms, GPU_Target* gpu_target) {
  // Prepares all of the lightable objects and draws them
  auto lightables = entity_manager.getEntities(interests);
  std::unordered_map<Transform, std::shared_ptr<Image>> objects;
  for (const auto& entity : lightables) {
    auto transform = entity_manager.getComponent<TransformComponent>(entity);
    auto render = entity_manager.getComponent<RenderComponent>(entity);
    auto collidable = entity_manager.getComponent<CollidableComponent>(entity);
    if (collidable != nullptr) {
      objects[transform->transform] = render->getImage();
    }
  }

  // Saves the lights to a list, and draws each light
  auto lights = entity_manager.getEntities(requirements);
  std::vector<std::pair<Transform, std::shared_ptr<Light>>> light_list;
  for (const auto& entity : lights) {
    auto transform = entity_manager.getComponent<TransformComponent>(entity);
    auto light = entity_manager.getComponent<LightComponent>(entity);
    light_list.push_back(std::pair<Transform, std::shared_ptr<Light>>(
        transform->transform,
        light->light));
    light->light->draw(gpu_target,
                       transform->transform.position,
                       objects);
  }

  // Draws each object
  shader->setLights(light_list);
  for (const auto& entity : lightables) {
    auto transform = entity_manager.getComponent<TransformComponent>(entity);
    auto render = entity_manager.getComponent<RenderComponent>(entity);
    auto collidable = entity_manager.getComponent<CollidableComponent>(entity);
    render->getImage()->draw(
        gpu_target,
        transform->transform.position.x,
        transform->transform.position.y,
        transform->transform.rotation.angle(),
        &(*shader));
  }
}
