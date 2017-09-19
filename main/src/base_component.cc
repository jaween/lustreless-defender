#include "base_component.h"

// Starts per-type unique IDs from 0
std::atomic<ComponentId> BaseComponent::next_id(0);
