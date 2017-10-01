#include <SDL2/SDL.h>
#include "SDL_gpu.h"

#include "game_over_component.h"
#include "game_over.h"


GameOver::GameOver(EntityManager& entity_manager)
    : Renderer(entity_manager) {
  requirements = {
    GameOverComponent::getTypeId()
  };

  text = std::unique_ptr<Image>(new Image("main/assets/sprites/game_over.png"));
  restart =
      std::unique_ptr<Image>(new Image("main/assets/sprites/restart.png"));
  started = false;
}

void GameOver::render(long ms, GPU_Target* gpu_target) {
  auto entities = entity_manager.getEntities(requirements);

  if (entities.size() > 0) {
    if (!started) {
      started = true;
      amount = 1;
    }
    amount += 0.06;

    text->draw(
        gpu_target,
        0,
        10 * sin(amount) + 100,
        text->getWidth() * (1 + 0.05 * sin(amount)),
        text->getHeight() * (1 + 0.05 * sin(amount)),
        0);

    restart->draw(gpu_target, 0, -100);
  } else {
    started = false;
  }
}
