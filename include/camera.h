#ifndef CAMERA_H_
#define CAMERA_H_

#include "glm/glm.hpp"

#include "vector.h"

class Camera {
 public:
  Camera(uint16_t width, uint16_t height);
  void setOrthographic(uint16_t width, uint16_t height);
  void setOrthographic(float left, float right, float bottom, float top);
  void setPosition(const Vector& position);
  Vector getPosition() const;
  glm::mat4 getViewProjectionMatrix();
  glm::mat4 getInverseViewProjectionMatrix();

 private:
  Vector position;
  Vector direction;
  glm::mat4 projection_matrix;
  glm::mat4 view_projection_matrix;
};

#endif // CAMERA_H_
