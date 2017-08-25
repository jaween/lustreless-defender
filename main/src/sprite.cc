#include "sprite.h"

Sprite::Sprite(std::string filename) {
  image = new Image(filename.c_str());
}

Sprite::~Sprite() {
  delete image;
}

uint16_t Sprite::getWidth() const {
  return image->getWidth();
}

uint16_t Sprite::getHeight() const {
  return image->getHeight();
}

void Sprite::update(uint64_t millis) {
  // TODO(jaween): Add to frame counter and implement animation
}

void Sprite::draw(GPU_Target* gpu_target, float x, float y) const {
  image->draw(gpu_target, 0, 0);
}
