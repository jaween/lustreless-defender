#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "vector.h"

class Transform {
 public:
  Transform();
  Vector position;
  Vector rotation;
};

// std::unordered_map needs this function at the global namespace
bool operator==(const Transform& lhs, const Transform& rhs);

#endif // TRANSFORM_H_
