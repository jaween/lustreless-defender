#include "entity_old.h"

EntityOld::EntityOld() {
  position = Vector(0, 0);
}

EntityOld::EntityOld(Vector& position) {
  this->position = position;
}

void EntityOld::update() {
  // Default empty implementation
}

void EntityOld::setPosition(Vector position) {
  this->position = position;
}

Vector EntityOld::getPosition() {
  return position;
}
