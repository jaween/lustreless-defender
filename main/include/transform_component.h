#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

#include "component.h"
#include "transform.h"

class TransformComponent : public Component<TransformComponent> {
 public:
  TransformComponent();
  Transform transform;
};

#endif // TRANSFORM_COMPONENT_H_
