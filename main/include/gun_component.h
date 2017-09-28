#ifndef GUN_COMPONENT_H_
#define GUN_COMPONENT_H_

#include <vector>

#include "component.h"
#include "transform.h"

class GunComponent : public Component<GunComponent> {
 public:
  GunComponent();
  void setNodes(const std::vector<Transform>& nodes);

  std::vector<Transform> nodes;
  int8_t last_used_index;
  uint32_t last_shoot_time;
};

#endif // GUN_COMPONENT_H_
