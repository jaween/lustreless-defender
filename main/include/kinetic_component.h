#ifndef KINETIC_COMPONENT_H_
#define KINETIC_COMPONENT_H_

#include "component.h"
#include "vector.h"

class KineticComponent : public Component<KineticComponent> {
 public:
  Vector velocity;
};

#endif // KINETIC_COMPONENT_H_
