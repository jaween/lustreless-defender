#include <SDL2/SDL2_gfxPrimitives.h>
#include <algorithm>

#include "wave.h"

const float Wave::kMinArcLength = 1.0f;
const float Wave::kAngleDelta = 1.0f * M_PI / 180;
const float Wave::kSpeed = 1.0f;
const float Wave::kMaxRadius = 500.0f;

Wave::Wave(Vector& origin,
    const Vector& start_vector,
    const Vector& end_vector,
    float initial_radius,
    std::vector<Wave*>& waves)
    : Entity(origin),
      origin(origin),
      start_vector(start_vector),
      end_vector(end_vector),
      waves(waves) {
  temp_should_destroy = false;
  radius = initial_radius;

  // TODO(jaween): Defining the edges in the wave is temp
  edges[0].set(500, 20);
  edges[1].set(400, 400);

  edges[2].set(450, 250);
  edges[3].set(150, 430);

  edges[4].set(60, 30);
  edges[5].set(200, 200);
}

void Wave::update() {
  Vector dir = Vector((start_vector.angle() + end_vector.angle()) / 2);
  radius += kSpeed;
  position = origin + radius * dir;

  // Computes the intersections with the walls
  for (int i = 0; i < 6; i += 2) {
    Vector wall_start = edges[i];
    Vector wall_end = edges[i + 1];
    lineSegIntersection(wall_start, wall_end);
  }

  if (!isValidArc(start_vector, end_vector, radius) || radius > kMaxRadius) {
    destroy();
  }
}

void Wave::draw(SDL_Renderer* renderer) {
  // Draws the walls
  for (int i = 0; i < 6; i += 2) {
    Vector s = edges[i];
    Vector e = edges[i + 1];
    SDL_SetRenderDrawColor(renderer, 0x00, 0xCC, 0x00, 0xFF);
    SDL_RenderDrawLine(renderer, s.x, s.y, e.x, e.y);
  }

  arcColor(
      renderer,
      (int) origin.x,
      (int) origin.y,
      radius,
      start_vector.angle() * 180 / M_PI,
      end_vector.angle() * 180 / M_PI,
      0xFFFFFFFF);
}

void Wave::lineSegIntersection(const Vector& start, const Vector& end) {
  float alpha = end.x - start.x;
  float beta = start.x - origin.x;
  float gamma = end.y - start.y;
  float epsilon = start.y - origin.y;

  float A = alpha * alpha + gamma * gamma;
  float B = 2 * alpha * beta + 2 * gamma * epsilon;
  float C = beta * beta + epsilon * epsilon - radius * radius;

  float determinant = B*B - 4 * A * C;
  if (determinant < 0) {
    // No intersection
    return;
  }

  // Line intersected circle
  float t1 = (-B + sqrt(determinant)) / (2 * A);
  float t2 = (-B - sqrt(determinant)) / (2 * A);

  performArcLineSegIntersection(start, end, t1, t2);
}

void Wave::performArcLineSegIntersection(
    const Vector& s,
    const Vector& e,
    float t1,
    float t2) {
  // Checks if the first point is on both the line and the arc
  bool t1_valid = false;
  Vector t1_dir;
  if (t1 >= 0 && t1 <= 1) {
    Vector point = s + t1 * (e - s);
    t1_valid = pointWithinSector(point, origin, start_vector, end_vector);
    t1_dir = point - origin;
  }

  // Checks if the second point is on both the line and the arc
  bool t2_valid = false;
  Vector t2_dir;
  if (t2 >= 0 && t2 <= 1) {
    Vector point = s + t2 * (e - s);
    t2_valid = pointWithinSector(point, origin, start_vector, end_vector);
    t2_dir = point - origin;
  }

  if (!(t1_valid || t2_valid)) {
    return;
  }

  // Generates direction vectors for the two smaller arcs that this arc will
  // split into
  Vector throwaway;
  Vector out_start_dir_a, out_end_dir_a;
  Vector out_start_dir_b, out_end_dir_b;
  if (t1_valid && t2_valid) {
    if (t1_dir.isClockWiseOf(t2_dir)) {
      // Swap
      Vector temp = t1_dir;
      t1_dir = t2_dir;
      t2_dir = temp;
    }
    cutArc(start_vector, end_vector, t1_dir, out_start_dir_a, out_end_dir_a,
        throwaway, throwaway);
    cutArc(start_vector, end_vector, t2_dir, throwaway, throwaway,
        out_start_dir_b, out_end_dir_b);
  } else {
    Vector t_dir = t1_valid ? t1_dir : t2_dir;
    cutArc(start_vector, end_vector, t_dir, out_start_dir_a, out_end_dir_a,
        out_start_dir_b, out_end_dir_b);
  }

  // This portion of the arc could be on the other side of the line. We check
  // this by casting a ray from the origin
  bool start_a_intersects = rayLineSegIntersection(origin, out_start_dir_a,
      radius + 2 * kSpeed, s, e);
  bool end_a_intersects = rayLineSegIntersection(origin, out_end_dir_a,
      radius + 2 * kSpeed, s, e);
  if (start_a_intersects && !end_a_intersects) {
    // TODO(jaween): Clip the angle properly instead of increasing the angle
    out_start_dir_a = Vector(out_start_dir_a.angle() + kAngleDelta);
  } else if (end_a_intersects && !start_a_intersects) {
    // TODO(jaween): Clip the angle properly instead of reducing the angle
    out_end_dir_a = Vector(out_end_dir_a.angle() + kAngleDelta);
  }

  // Creates a new wave for the portion of the arc counter-clockwise to the
  //  intersection
  if (isValidArc(out_start_dir_a, out_end_dir_a, radius)) {
    if (!(start_a_intersects && end_a_intersects)) {
      Wave* wave = new Wave(origin, out_start_dir_a, out_end_dir_a, radius,
          waves);
      waves.push_back(wave);
    }
  }

  // This portion of the arc could be on the other side of the line. We check
  // this by casting a ray from the origin
  bool start_b_intersects = rayLineSegIntersection(origin, out_start_dir_b,
      radius + 2 * kSpeed, s, e);
  bool end_b_intersects = rayLineSegIntersection(origin, out_end_dir_b,
      radius + 2 * kSpeed, s, e);
  if (start_b_intersects && !end_b_intersects) {
  // TODO(jaween): Clip the angle properly instead of increasing the angle
    out_start_dir_b = Vector(out_start_dir_b.angle() + kAngleDelta);
  } else if (end_b_intersects && !start_b_intersects) {
  // TODO(jaween): Clip the angle properly instead of reducing the angle
    out_end_dir_b = Vector(out_end_dir_b.angle() - kAngleDelta);
  }

  // Shortens this wave clockwise up to the point of intersection
  if (isValidArc(out_start_dir_b, out_end_dir_b, radius)
      && !(start_b_intersects && end_b_intersects)) {
  start_vector = out_start_dir_b;
  end_vector = out_end_dir_b;
  } else {
    destroy();
  }
}

bool Wave::isValidArc(
    const Vector& start_dir,
    const Vector& end_dir,
    float radius) const {
  bool clock_wise = end_dir.isClockWiseOf(start_dir);
  bool equal = start_dir == end_dir;
  bool nan = std::isnan(start_dir.angleBetween(end_dir));
  bool too_short = getArcLength(start_dir, end_dir, radius) < kMinArcLength;
  return clock_wise && !equal && !nan && !too_short;
}

void Wave::cutArc(
    const Vector& start_dir,
    const Vector& end_dir,
    const Vector& cut_dir,
    Vector& out_start_dir_a,
    Vector& out_end_dir_a,
    Vector& out_start_dir_b,
    Vector& out_end_dir_b) {
  float start_angle = start_dir.angle();
  float end_angle = end_dir.angle();
  float cut_angle = cut_dir.angle();

  // Arc before the t value
  out_start_dir_a = start_dir;
  out_end_dir_a = Vector(cut_angle - kAngleDelta);

  // Arc after the t value
  out_start_dir_b = Vector(cut_angle + kAngleDelta);
  out_end_dir_b = end_dir;
}

bool Wave::pointWithinSector(
    const Vector& point,
    const Vector& origin,
    const Vector& start_dir,
    const Vector& end_dir) {
  Vector translated_point = point - origin;
  float spread = start_dir.angleBetween(end_dir);
  float angle_from_start = start_dir.angleBetween(translated_point);
  float angle_from_end = end_dir.angleBetween(translated_point);

  return angle_from_start <= spread && angle_from_end <= spread;
}

bool Wave::lineSegLineSegIntersection(
    const Vector& a,
    const Vector& b,
    const Vector& p,
    const Vector& q) {
  // Based on Gavin's answer here: https://stackoverflow.com/a/1968345
  Vector s1 = b - a;
  Vector s2 = q - p;

  float s, t;
  float denominator = -s2.x * s1.y + s1.x * s2.y;
  s = (-s1.y * (a.x - p.x) + s1.x * (a.y - p.y)) / denominator;
  t = ( s2.x * (a.y - p.y) - s2.y * (a.x - p.x)) / denominator;

  return s >= 0 && s <= 1 && t >= 0 && t <= 1;
}

bool Wave::rayLineSegIntersection(
    const Vector& origin,
    const Vector& dir,
    float length,
    const Vector& a,
    const Vector& b) {
  Vector radius_ray_end = origin + length * dir;
  return lineSegLineSegIntersection(origin, radius_ray_end, a, b);
}

float Wave::getArcLength(const Vector& start, const Vector& end, float radius) {
  return radius * start.angleBetween(end);
}

void Wave::printArc(const Vector& s, const Vector& e) {
  float angle_s = s.angle() * 180 / M_PI;
  float angle_e = e.angle() * 180 / M_PI;
  float spread = s.angleBetween(e) * 180 / M_PI;
  std::clog << " Arc (" << angle_s << ", " << angle_e << ") spread of " 
      << spread << std::endl;
}

void Wave::destroy() {
  // Marks the wave to be destroyed if the start and end have crossed
  // TODO(jaween): Implement a way to acually destroy a wave from here
  start_vector.set(0, 0);
  end_vector.set(0, 0);
  temp_should_destroy = true;
}

bool Wave::tempShouldDestroy() {
  return temp_should_destroy;
}
