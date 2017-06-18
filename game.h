#ifndef SCENE_H_
#define SCENE_H_

#include <SDL2/SDL.h>

class Scene {
 public:
  void init();
  void update();
  void draw(SDL_Renderer* renderer);
  void finish();
};

#endif // GAME_H_
