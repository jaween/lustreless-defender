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
  int16_t getWidth() const;
  int16_t getHeight() const;

  template<class T>
  std::shared_ptr<T> addProcessor() {
    std::shared_ptr<Processor> processor =
        std::shared_ptr<T>(new T(entity_manager));
    processors.push_back(processor);
    addRequirements(processor);
    return std::static_pointer_cast<T>(processor);
  }

  template<class T>
  std::shared_ptr<T> addRenderer() {
    std::shared_ptr<Renderer> renderer =
        std::shared_ptr<T>(new T(entity_manager));
    renderers.push_back(renderer);
    addRequirements(renderer);
    return std::static_pointer_cast<T>(renderer);
  }

 private:
  static const int16_t kScreenWidth;
  static const int16_t kScreenHeight;

  GPU_Target* window;
  EntityManager& entity_manager;
  std::vector<std::shared_ptr<Processor>> processors;
  std::vector<std::shared_ptr<Renderer>> renderers;

  bool init();
  void addRequirements(const std::shared_ptr<Processor>& p);
};

#endif // ENGINE_H_
