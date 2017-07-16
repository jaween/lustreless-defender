#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>

#include "image.h"

/**
 * Represents an animated set of images.
 */
class Sprite {
 public:
  Sprite(std::string filename);
  ~Sprite();
  uint16_t getWidth() const;
  uint16_t getHeight() const;
  void update(uint64_t milis);
  void draw(GPU_Target* gpu_target, float x, float y) const;

 private:
  Image* image;
};

#endif // SPRITE_H_
