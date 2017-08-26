#include "component.h"

std::atomic<uint32_t> Component::next_id(0);

Component::~Component() {
  // Abstract class
}
