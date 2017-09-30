#ifndef COLLIDABLE_COMPONENT_H_
#define COLLIDABLE_COMPONENT_H_

#include "component.h"

class CollidableComponent : public Component<CollidableComponent> {
 public:
  CollidableComponent();
  void setRadius(uint16_t radius);
  uint16_t radius;
};

#endif // COLLIDABLE_COMPONENT_H_
