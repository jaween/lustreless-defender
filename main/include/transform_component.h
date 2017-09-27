#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

#include "component.h"
#include "vector.h"

class TransformComponent : public Component<TransformComponent> {
 public:
  TransformComponent();
  Vector position;
};

#endif // TRANSFORM_COMPONENT_H_
