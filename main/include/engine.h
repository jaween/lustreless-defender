#ifndef ENGINE_H_
#define ENGINE_H_

#include "SDL_gpu.h"
#include <memory>

#include "entity_manager.h"
#include "processor.h"
#include "renderer.h"

// Forward declaration due to circular dependence between Engine and Room
class Room;

class Engine {
 public:
  Engine(EntityManager& entity_manager);
  ~Engine();
  void run(Room& room);

  template<class T>
  void addProcessor() {
    auto processor = std::shared_ptr<T>(new T(entity_manager));
    auto requirements = processor->chooseRequirements();
    auto pair = std::pair<std::shared_ptr<Processor>, Requirements>(
        processor, requirements);
    processors.push_back(pair);
    entity_manager.addRequirements(requirements);
  }

  template<class T>
  void addRenderer() {
    auto renderer = std::shared_ptr<T>(new T(entity_manager));
    auto requirements = renderer->chooseRequirements();
    auto pair = std::pair<std::shared_ptr<Renderer>, Requirements>(
        renderer, requirements);
    renderers.push_back(pair);
    addProcessor<T>();
  }

 private:
  static const int kScreenWidth;
  static const int kScreenHeight;

  GPU_Target* window;
  EntityManager& entity_manager;
  std::vector<std::pair<std::shared_ptr<Processor>, Requirements>> processors;
  std::vector<std::pair<std::shared_ptr<Renderer>, Requirements>> renderers;

  bool init();
};

#endif // ENGINE_H_
