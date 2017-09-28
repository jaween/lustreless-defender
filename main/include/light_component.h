#ifndef LIGHT_COMPONENT_H_
#define LIGHT_COMPONENT_H_

#include <SDL/SDL.h>
#include <memory>

#include "component.h"
#include "light.h"

class LightComponent : public Component<LightComponent> {
 public:
  LightComponent();
  void setParameters(SDL_Color colour, uint16_t);
  std::shared_ptr<Light> light;
};

#endif // LIGHT_COMPONENT_H_
