#include "transform.h"

Transform::Transform() {
  rotation.set(1, 0);
}

bool operator==(const Transform& lhs, const Transform& rhs) {
  return lhs.position == rhs.position && lhs.rotation == rhs.rotation;
}
