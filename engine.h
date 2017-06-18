#ifndef ENGINE_H_
#define ENGINE_H_

#include <SDL2/SDL.h>

#include "room.h"

class Engine {
 public:
  Engine(const Room& room);
  void run();

 private:
  int kScreenWidth = 640;
  int kScreenHeight= 480;

  SDL_Window* window;
  SDL_Renderer* renderer;
  Room room;

  bool init();
  void finish();
};

#endif // ENGINE_H_
