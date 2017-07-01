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
      std::vector<Wave*>& waves,
      int age);
  virtual void update();
  virtual void draw(SDL_Renderer* renderer);
  bool tempShouldDestroy();
  Vector getOrigin() const;
  float getRadius() const;
  Vector getStart() const;
  Vector getEnd() const;
  void checkIfMovedThroughWall(const Vector& s, const Vector& e);

 private:
  static const float kMinArcLength;
  static const float kAngleDelta;
  static const float kSpeed;
  static const float kMaxRadius;

  std::vector<Wave*>& waves;
  Vector origin;
  Vector start_vector;
  Vector end_vector;
  Vector center_dir;
  float radius;
  Vector edges[8];
  bool temp_should_destroy;
  int age;

  // Helper functions
  static float getArcLength(const Vector& start, const Vector& end,
       float radius);
  static bool pointWithinSector(const Vector& point, const Vector& origin,
      const Vector& start_dir, const Vector& end_dir);
  static bool lineSegLineSegIntersection(const Vector& a, const Vector& b,
      const Vector& p, const Vector& q, Vector& out);

  static void printArc(const Vector& s, const Vector& e);

  void lineSegIntersection(const Vector& start, const Vector& end);
  bool performArcLineSegIntersection(const Vector& s, const Vector& e, float t1,
      float t2);
  void cutArc(const Vector& start_dir, const Vector& end_dir,
      const Vector& cut_dir, Vector& out_start_dir_a, Vector& out_end_dir_a,
      Vector& out_start_dir_b, Vector& out_end_dir_b);
  bool reflect(const Vector& origin,const Vector& point1, const Vector& point2,
      const Vector& line_seg_start, const Vector& line_seg_end);
  bool rayLineSegIntersection(const Vector& origin, const Vector& dir,
      float length, const Vector& a, const Vector& b, Vector& out);
  bool rayLineIntersection(const Vector& ray_origin, const Vector& ray_dir,
      const Vector& line_point, const Vector& line_dir, Vector& out);
  bool isValidArc(const Vector& start_dir, const Vector& end_dir,
      float radius) const;
  void destroy();
};

bool operator==(const Wave& lhs, const Wave& rhs);

#endif // WAVE_H_
