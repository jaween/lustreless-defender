#ifndef GAME_OVER_H_
#define GAME_OVER_H_

#include <memory>

#include "image.h"
#include "renderer.h"

class GameOver : public Renderer {
 public:
  GameOver(EntityManager& entity_manager);
  virtual void render(long ms, GPU_Target* gpu_target);

 private:
  std::unique_ptr<Image> text;
  std::unique_ptr<Image> restart;
  bool started;
  float amount;
};

#endif // MOVEMENT_H_

