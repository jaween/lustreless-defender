#ifndef ROOM_H_
#define ROOM_H_

#include "SDL_gpu.h"
#include <vector>

#include "highlight_shader.h"
#include "image.h"
#include "light.h"
#include "wave.h"

class Room {
 public:
  void init();
  void update();
  void draw(GPU_Target* gpu_target);
  void finish();

 private:
  int angle;
  std::vector<Wave*> waves;
  Image* image;
  int light_count;
  std::vector<Light*> lights;
  HighlightShader* highlight_shader;

  void mergeWaves();
  void printWaves();
};

#endif // ROOM_H_
