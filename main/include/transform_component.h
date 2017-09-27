#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

#include "component.h"

class TransformComponent : public Component<TransformComponent> {
 public:
  TransformComponent();
  int x;
  int y;
};

#endif // TRANSFORM_COMPONENT_H_
