#include "collidable_component.h"

CollidableComponent::CollidableComponent() {
  radius = 0;
}

void CollidableComponent::setRadius(uint16_t radius) {
  this->radius = radius;
}
