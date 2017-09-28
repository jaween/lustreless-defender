#include "gun_component.h"

GunComponent::GunComponent() {
  last_used_index = 0;
  last_shoot_time = 0;
}

void GunComponent::setNodes(const std::vector<Transform>& nodes) {
  this->nodes = nodes;
  last_used_index = 0;
}
