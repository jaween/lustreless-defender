#ifndef WAVE_H_
#define WAVE_H_

#include <vector>

#include "entity.h"
#include "vector.h"

class Wave : public Entity {
 public:
  Wave(Vector& origin,
      const Vector& start_vector,
      const Vector& end_vector,
      float initial_radius,
      std::vector<Wave*>& waves);
  virtual void update();
  virtual void draw(SDL_Renderer* renderer);
  bool tempShouldDestroy();

 private:
  static const float kMinArcLength;
  static const float kAngleDelta;
  static const float kSpeed;
  static const float kMaxRadius;

  std::vector<Wave*>& waves;
  Vector origin;
  Vector start_vector;
  Vector end_vector;
  float radius;
  Vector edges[6];
  bool temp_should_destroy;

  // Helper functions
  static float getArcLength(const Vector& start, const Vector& end, float radius);
  static bool pointWithinSector(const Vector& point, const Vector& origin,
      const Vector& start_dir, const Vector& end_dir);
  static bool lineSegLineSegIntersection(const Vector& a, const Vector& b,
      const Vector& p, const Vector& q);

  static void printArc(const Vector& s, const Vector& e);

  void lineSegIntersection(const Vector& start, const Vector& end);
  void performArcLineSegIntersection(const Vector& s, const Vector& e, float t1,
      float t2);
  void cutArc(const Vector& start_dir, const Vector& end_dir,
      const Vector& cut_dir, Vector& out_start_dir_a, Vector& out_end_dir_a,
      Vector& out_start_dir_b, Vector& out_end_dir_b);
  bool rayLineSegIntersection(const Vector& origin, const Vector& dir,
      float length, const Vector& a, const Vector& b);
  bool isValidArc(const Vector& start_dir, const Vector& end_dir,
      float radius) const;
  void destroy();
};

#endif // WAVE_H_
