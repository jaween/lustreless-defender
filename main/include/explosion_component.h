#ifndef EXPLOSION_COMPONENT_H_
#define EXPLOSION_COMPONENT_H_

#include "component.h"

class ExplosionComponent : public Component<ExplosionComponent> {
 public:
  ExplosionComponent();
  int remaining;
};

#endif // EXPLOSION_COMPONENT_H_
