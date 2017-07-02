#ifndef ROOM_H_
#define ROOM_H_

#include "SDL_gpu.h"
#include <vector>

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

  void mergeWaves();
  void printWaves();
};

#endif // ROOM_H_
