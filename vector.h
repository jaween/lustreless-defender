#ifndef VECTOR_H_
#define VECTOR_H_

#include <functional>
#include <iostream>

class Vector {
 public:
  // TODO(jaween): Make private and enforce x() and y() to access values?
  float x;
  float y;
  Vector();
  Vector(float angle);
  Vector(float x, float y);
  Vector(Vector&& other);
  Vector(const Vector& other);
  Vector& operator=(Vector&& other);
  Vector& operator=(const Vector& other);
  void set(float x, float y);
  float length() const;
  void normalise();
  void normalise(Vector& dest) const;
  float angle() const;
  float angleBetween(const Vector& other) const;
  bool isClockWiseOf(const Vector& other) const;
  void rotate(float angle);
  float dot(const Vector& other) const;
  bool operator<(const Vector& other) const;
  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;
  Vector operator-() const;
  Vector operator+=(const Vector& other);
  Vector operator-=(const Vector& other);
  Vector operator*=(float scale);
  friend Vector operator*(float scale, const Vector& vector);
  friend Vector operator*(const Vector& vector, float scale);
  friend std::ostream& operator<<(std::ostream& stream, const Vector& v);

  struct Hash {
    size_t operator()(const Vector& vector) const {
      return std::hash<int>()(vector.x) ^ std::hash<int>()(vector.y);
    }
  };

 private:
  void move(Vector&& other);
  void copy(const Vector& other);
};

// std::unordered_map needs this function at the global namespace
bool operator==(const Vector& lhs, const Vector& rhs);

#endif // VECTOR_H_
