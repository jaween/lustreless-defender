#include <cmath>
#include <utility>

#include "vector.h"

Vector::Vector() {
  set(0, 0);
}

Vector::Vector(float x, float y) {
  set(x, y);
}

Vector::Vector(float angle) {
  set(cos(angle), sin(angle));
}

Vector::Vector(Vector&& other) {
  move(std::move(other));
}

Vector::Vector(const Vector& other) {
  copy(other);
}

Vector& Vector::operator=(Vector&& other) {
 move(std::move(other));
  return *this;
}

Vector& Vector::operator=(const Vector& other) {
  copy(other);
  return *this;
}

void Vector::set(float x, float y) {
  this->x = x;
  this->y = y;
}

float Vector::length() const {
  return sqrt(x * x + y * y);
}

void Vector::normalise() {
  float len = length();
  x /= len;
  y /= len;
}

void Vector::normalise(Vector& dest) const {
  float len = length();
  dest.x = x / len;
  dest.y = y / len;
}

float Vector::angle() const {
  return atan2(y, x);
}

float Vector::angleBetween(const Vector& other) const {
  Vector norm(*this);
  norm.normalise();

  Vector norm_other(other);
  norm_other.normalise();

  return acos(norm.x * norm_other.x + norm.y * norm_other.y);
}

bool Vector::isClockWiseOf(const Vector& other) const {
  // Sign of z-component of cross product
  return (x * other.y - y * other.x) < 0;
}

void Vector::rotate(float angle) {
  float c = cos(angle);
  float s = sin(angle);
  float new_x = x * c - y * s;
  float new_y = x * s + y * c;
  x = new_x;
  y = new_y;
}

float Vector::dot(const Vector& other) const {
  return x * other.x + y * other.y;
}

bool Vector::operator<(const Vector& other) const {
  return x == other.x ? y < other.y : x < other.x;
}

Vector Vector::operator+(const Vector& other) const {
  return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const {
  return Vector(x - other.x, y - other.y);
}

Vector Vector::operator-() const {
  return Vector(-x, -y);
}

Vector Vector::operator*=(float scale) {
  x *= scale;
  y *= scale;
  return *this;
}

Vector operator*(float scale, const Vector& vector) {
  return Vector(vector.x * scale, vector.y * scale);
}

Vector operator*(const Vector& vector, float scale) {
  return Vector(vector.x * scale, vector.y * scale);
}

std::ostream& operator<<(std::ostream& stream, const Vector& v) {
  stream << "[" << v.x << ", " << v.y << "]";
  return stream;
}

void Vector::move(Vector&& other) {
  if (&other != this) {
    x = other.x;
    y = other.y;
    other.x = 0;
    other.y = 0;
  }
}

void Vector::copy(const Vector& other) {
  x = other.x;
  y = other.y;
}

bool operator==(const Vector& lhs, const Vector& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
