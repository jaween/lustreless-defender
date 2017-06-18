#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL2/SDL.h>

#include "vector.h"

class Entity {
 public:
  Entity(Vector& position);
  virtual void update();
  virtual void draw(SDL_Renderer* renderer) = 0;

 protected:
  Vector position;
};

#endif // ENTITY_H_
