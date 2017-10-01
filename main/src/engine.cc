#include "GL/glew.h"
#include <iostream>
#include <vector>

#include "engine.h"
#include "game_over_component.h"
#include "room.h"

const int16_t Engine::kScreenWidth = 480;
const int16_t Engine::kScreenHeight = 640;

Engine::Engine(EntityManager& entity_manager)
    : entity_manager(entity_manager) {
  std::clog << "Jaween's light engine started" << std::endl;
}

Engine::~Engine() {
  GPU_Quit();

  std::clog << "Jaween's light engine ended" << std::endl;
}

void Engine::run(Room& room) {
  if (!init()) {
    return;
  }

  room.init();

  bool keep_running = true;
  bool game_over = false;
  while (keep_running) {
    // Input handling
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0) {
      switch (event.type) {
        case SDL_QUIT:
          keep_running = false;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_RETURN && game_over) {
            processors.clear();
            renderers.clear();
            entity_manager.clear();
            room.init();
            game_over = false;
          }
      }
    }

    Requirements r = { GameOverComponent::getTypeId() };
    auto game_over_entities = entity_manager.getEntities(r);
    if (game_over_entities.size() != 0) {
      game_over = true;
    }

    if (!game_over) {
      room.update();
      for (const auto& processor : processors) {
        const long temp_update_ms = 16;
        processor->update(temp_update_ms);
      }
    }

    SDL_Color color = { 0x00, 0x00, 0x00, 0x00 };
    GPU_ClearColor(window, color);
    room.draw(window);
    for (const auto& renderer : renderers) {
      const long temp_update_ms = 16;
      renderer->render(temp_update_ms, window);
    }

    // Removes the entities which have been marked to be deleted
    for (const auto& processor : processors) {
      const auto entities_to_delete = processor->getEntitiesToDelete();
      for (const auto& entity : entities_to_delete) {
        entity_manager.deleteEntity(entity);
      }
    }

    GPU_Flip(window);
    SDL_Delay(10);
  }
}

bool Engine::init() {
  GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

  window = GPU_Init(kScreenWidth, kScreenHeight, GPU_DEFAULT_INIT_FLAGS);
  if (window == nullptr) {
    std::cerr << "Failed to initialise SDL_gpu: " << std::endl;
    return false;
  }

  // Initialises GLEW (loads OpenGL extension functions that we can then call)
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    GPU_LogError("Failed to initialise GLEW\n");
    return false;
  }

  return true;
}

void Engine::addRequirements(const std::shared_ptr<Processor>& p) {
  auto requirements = p->getRequirements();
  if (requirements.size() > 0) {
    entity_manager.addRequirements(requirements);
  }

  auto interests = p->getInterests();
  if (interests.size() > 0) {
    entity_manager.addRequirements(interests);
  }
}

int16_t Engine::getWidth() const {
  return kScreenWidth;
}

int16_t Engine::getHeight() const {
  return kScreenHeight;
}
