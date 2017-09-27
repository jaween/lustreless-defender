#include "light_component.h"

LightComponent::LightComponent() {
  SDL_Color colour = { 0xFF, 0xFF, 0xFF, 0xFF };
  light = std::make_shared<Light>(colour);
}

void LightComponent::setColour(SDL_Color colour) {
  light->setColour(colour);
}
