#include "light_component.h"

LightComponent::LightComponent() { }

void LightComponent::setParameters(SDL_Color colour, uint16_t size) {
 light = std::make_shared<Light>(colour, size);
}
