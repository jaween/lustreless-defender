#include "SDL_gpu.h"
#include "glm/gtc/matrix_transform.hpp"

#include "camera.h"

Camera::Camera(uint16_t width, uint16_t height) {
  setOrthographic(width, height);
}

void Camera::setOrthographic(uint16_t width, uint16_t height) {
  // Inverted y-coordinate to match screen coordinate system
  projection_matrix = glm::ortho(
      -width / 2.0f,
      width / 2.0f,
      height / 2.0f,
      -height / 2.0f);

  setPosition(position);
}

void Camera::setOrthographic(float left, float right, float bottom,
    float top) {
  projection_matrix = glm::ortho(left, right, bottom, top);
  setPosition(position);
}

void Camera::setPosition(const Vector& position) {
  this->position = position;

  // We're really moving the objects relative to the camera
  // Inverted y-coordinate to match screen coordinate system
  view_projection_matrix = glm::translate(projection_matrix,
      glm::vec3(-position.x, position.y, 0.0f));
}

Vector Camera::getPosition() const {
  return position;
}

glm::mat4 Camera::getViewProjectionMatrix() {
  return view_projection_matrix;
}

glm::mat4 Camera::getInverseViewProjectionMatrix() {
  return glm::inverse(view_projection_matrix);
}
