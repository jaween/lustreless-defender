#ifndef ENGINE_H_
#define ENGINE_H_

#include <SDL2/SDL.h>

class Engine {
 public:
  Engine();
  void run();

 private:
  int kScreenWidth = 640;
  int kScreenHeight= 480;

  SDL_Window* window;
  SDL_Surface* screen_surface;

  bool init();
  void update();
  void draw();
  void finish();
};

#endif // ENGINE_H_
