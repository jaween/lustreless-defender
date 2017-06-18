#ifndef VECTOR_H_
#define VECTOR_H_

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
  float length();
  void normalise();
  void normalise(Vector& dest);
  float angle() const;
  float angleBetween(const Vector& other) const;
  bool isClockWiseOf(const Vector& other) const;
  float dot(const Vector& other) const;
  bool operator==(const Vector& other) const;
  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;
  Vector operator*=(float scale);
  friend Vector operator*(float scale, const Vector& vector);
  friend Vector operator*(const Vector& vector, float scale);
  friend std::ostream& operator<<(std::ostream& stream, const Vector& v);

 private:
  void move(Vector&& other);
  void copy(const Vector& other);
};

#endif // VECTOR_H_
