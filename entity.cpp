#include "entity.h"

Entity::Entity() {
  position = Vector(0, 0);
}

Entity::Entity(Vector& position) {
  this->position = position;
}

void Entity::update() {
  // Default empty implementation
}

void Entity::setPosition(Vector position) {
  this->position = position;
}

Vector Entity::getPosition() {
  return position;
}
