#include "component.h"

// Starts per-type unique IDs from 0
std::atomic<ComponentId> Component::next_id(0);
