#ifndef ENGINE_H_
#define ENGINE_H_

#include "SDL_gpu.h"
#include <memory>

#include "entity_manager.h"
#include "processor.h"

// Forward declaration due to circular dependence between Engine and Room
class Room;

class Engine {
 public:
  Engine();
  void run(Room& room);
  EntityManager& getEntityManager();

  template<class T>
  void addProcessor() {
    auto processor = std::shared_ptr<T>(new T);
    auto requirements = processor->chooseRequirements();
    auto pair = std::pair<std::shared_ptr<Processor>, Requirements>(
        processor, requirements);
    processors.push_back(pair);
    entity_manager.addRequirements(requirements);
  }

 private:
  static const int kScreenWidth;
  static const int kScreenHeight;

  GPU_Target* window;
  EntityManager entity_manager;
  std::vector<std::pair<std::shared_ptr<Processor>, Requirements>> processors;

  bool init();
  void finish();
};

#endif // ENGINE_H_
