#include <algorithm>

#include "wave.h"

const float Wave::kMinArcLength = 0.0f;
const float Wave::kAngleDelta = 0.0f * M_PI / 180;
const float Wave::kSpeed = 1.0f;
const float Wave::kMaxRadius = 500.0f;

Wave::Wave(Vector& origin,
    const Vector& start_vector,
    const Vector& end_vector,
    float initial_radius,
    std::vector<Wave*>& waves,
    int age)
    : EntityOld(origin),
      origin(origin),
      start_vector(start_vector),
      end_vector(end_vector),
      waves(waves),
      age(age) {
  temp_should_destroy = false;
  radius = initial_radius;
  this->start_vector.normalise();
  this->end_vector.normalise();

  // TODO(jaween): Temporary sanity check until all waves are created valid
  if (!isValidArc(start_vector, end_vector, radius)) {
    destroy();
  }

  // TODO(jaween): Defining the edges in the wave is temp
  edges[0].set(500, 20);
  edges[1].set(400, 400);

  edges[2].set(450, 250);
  edges[3].set(150, 430);

  edges[4].set(60, 30);
  edges[5].set(200, 200);

  edges[6].set(80, 460);
  edges[7].set(200, 300);
}

void Wave::update() {
  float angle = start_vector.angle() + start_vector.angleBetween(end_vector)/2;
  center_dir = Vector(angle);
  center_dir.normalise();

  radius += kSpeed;
  position = origin + radius * center_dir;

  // Computes the intersections with the walls
  for (int i = 0; i < 8; i += 2) {
    Vector wall_start = edges[i];
    Vector wall_end = edges[i + 1];
    lineSegIntersection(wall_start, wall_end);
  }

  if (!isValidArc(start_vector, end_vector, radius) || radius > kMaxRadius) {
    destroy();
  }

  age++;
}

void Wave::draw(GPU_Target* gpu_target) {
  // Draws the walls
  for (int i = 0; i < 8; i += 2) {
    Vector s = edges[i];
    Vector e = edges[i + 1];

    SDL_Color edge_colour = { 0x00, 0xCC, 0x00, 0xFF };
    GPU_Line(gpu_target, s.x, s.y, e.x, e.y, edge_colour);
  }

  // Draws the wavefront
  uint8_t alpha = 255 - 255 * (radius / kMaxRadius);
  SDL_Color arc_colour = { 0xFF, 0xFF, 0xFF, alpha };
  float spread = start_vector.angleBetween(end_vector) * 180 / M_PI;
  float start_angle = start_vector.angle() * 180 / M_PI;
  /*if (end_angle < start_angle) {
    float temp = end_angle;
    end_angle = start_angle;
    start_angle = temp;
  }*/
  GPU_Arc(
      gpu_target,
      (int) origin.x,
      (int) origin.y,
      radius,
      start_angle,
      start_angle + spread,
      arc_colour);

  // Origin
  SDL_Color origin_colour = { 0xFF, 0xFF, 0xFF, 0xFF };
  GPU_CircleFilled(
      gpu_target,
      (int) origin.x,
      (int) origin.y,
      3,
      origin_colour);

  // Line from origin to center of wavefront
  /*SDL_Color ray_colour = { 0xFF, 0x00, 0x00, alpha };
  GPU_Line(
      gpu_target,
      origin.x,
      origin.y,
      origin.x + (center_dir * radius).x,
      origin.y + (center_dir * radius).y,
      ray_colour);*/
}

Vector Wave::getOrigin() const {
  return origin;
}

float Wave::getRadius() const {
  return radius;
}

Vector Wave::getStart() const {
  return start_vector;
}

Vector Wave::getEnd() const {
  return end_vector;
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

  bool arc_line_seg_intersection =
      performArcLineSegIntersection(start, end, t1, t2);

  // Given that the arc didn't intersect the line, checks if the arc passed
  // through the line
  if (!arc_line_seg_intersection) {
    checkIfMovedThroughWall(start, end);
  }
}

bool Wave::performArcLineSegIntersection(
    const Vector& s,
    const Vector& e,
    float t1,
    float t2) {
  // Checks if the first point is on both the line and the arc
  bool t1_valid = false;
  Vector t1_point;
  if (t1 >= 0 && t1 <= 1) {
    t1_point = s + t1 * (e - s);
    t1_valid = pointWithinSector(t1_point, origin, start_vector, end_vector);
  }

  // Checks if the second point is on both the line and the arc
  bool t2_valid = false;
  Vector t2_point;
  if (t2 >= 0 && t2 <= 1) {
    t2_point = s + t2 * (e - s);
    t2_valid = pointWithinSector(t2_point, origin, start_vector, end_vector);
  }

  // From here onwards we can assume at least one point of intersection
  if (!(t1_valid || t2_valid)) {
    return false;
  }

  // Sets the collision points and direction vectors
  Vector t1_dir = t1_point - origin;
  Vector t2_dir = t2_point - origin;
  if (t1_valid && t2_valid) {
      if (t1_dir.isClockWiseOf(t2_dir)) {
      // Swaps collision points
      Vector temp = t1_point;
      t1_point = t2_point;
      t2_point = temp;

      // Swaps direction vectors
      temp = t1_dir;
      t1_dir = t2_dir;
      t2_dir = temp;
    }
  } else {
    t1_point = t1_valid ? t1_point : t2_point;
    t1_dir = t1_valid ? t1_dir : t2_dir;
  }

  // Generates direction vectors for the two smaller arcs that this arc will
  // split into
  Vector throwaway;
  Vector out_start_dir_a, out_end_dir_a;
  Vector out_start_dir_b, out_end_dir_b;
  if (t1_valid && t2_valid) {
    cutArc(start_vector, end_vector, t1_dir, out_start_dir_a, out_end_dir_a,
        throwaway, throwaway);
    cutArc(start_vector, end_vector, t2_dir, throwaway, throwaway,
        out_start_dir_b, out_end_dir_b);
  } else {
    cutArc(start_vector, end_vector, t1_dir, out_start_dir_a, out_end_dir_a,
        out_start_dir_b, out_end_dir_b);
  }

  bool start_a_intersects = rayLineSegIntersection(origin, out_start_dir_a,
      radius + 1 * kSpeed, s, e, throwaway);
  bool end_a_intersects = rayLineSegIntersection(origin, out_end_dir_a,
      radius + 1 * kSpeed, s, e, throwaway);
  bool start_b_intersects = rayLineSegIntersection(origin, out_start_dir_b,
      radius + 1 * kSpeed, s, e, throwaway);
  bool end_b_intersects = rayLineSegIntersection(origin, out_end_dir_b,
      radius + 1 * kSpeed, s, e, throwaway);
  if (t1_valid && t2_valid) {
      // Two points  of intersection with line segement
    reflect(origin, t1_dir, t2_dir, s, e);
    Wave* wave = new Wave(origin, out_start_dir_a, out_end_dir_a, radius,
        waves, age);
    waves.push_back(wave);
    start_vector = out_start_dir_b;
    end_vector = out_end_dir_b;
  } else {
    if (start_a_intersects && end_a_intersects) {
      // Single point of intersection with line segement
      if (reflect(origin, out_start_dir_a, t1_dir, s, e)) {
        start_vector = out_start_dir_b;
        end_vector = out_end_dir_b;
      }
    } else if (start_b_intersects && end_b_intersects) {
      // Single point of intersection with line segement
      if (reflect(origin, t1_dir, out_end_dir_b, s, e)) {
        start_vector = out_start_dir_a;
        end_vector = out_end_dir_a;
      }
    } else {
      // Edge case: single point of intersection near line segment tip

      // Flips the wall_dir vector such that the angle between it and t1_dir is
      // minimised
      Vector closer_point = s;
      Vector wall_dir = e - s;
      if (wall_dir.angleBetween(t1_dir) > M_PI / 2) {
        wall_dir = -wall_dir;
        closer_point = e;
      }

      // Here either the A or B section of the cut will have to be shortened
      // depending on whether angle from the origin to the intersection was
      // clockwise or counter-clockwise
      if (t1_dir.isClockWiseOf(wall_dir)) {
        // Shortens the B section of the cut
        Wave* wave = new Wave(origin, out_start_dir_a, out_end_dir_a, radius,
          waves, age);
        waves.push_back(wave);
        start_vector = closer_point - origin;
        end_vector = out_end_dir_b;

        // TODO(jaween): Reflect the portion of B which was shortened
        //reflect(origin, out_start_dir_b, closer_point - origin, s, e);
      } else {
        // Shortens the A section of the cut
        Wave* wave = new Wave(origin, out_start_dir_b, out_end_dir_b, radius,
          waves, age);
        waves.push_back(wave);
        start_vector = out_start_dir_a;
        end_vector = closer_point - origin;

        // TODO(jaween): Reflect the portion of A which was shortened
        //reflect(origin, closer_point - origin, out_end_dir_a, s, e);
      }
    }
  }

  return true;
}

bool Wave::reflect(
    const Vector& origin,
    const Vector& dir_start,
    const Vector& dir_end,
    const Vector& line_seg_start,
    const Vector& line_seg_end) {
  float ninety = 90 * M_PI / 180;
  float one_eighty = 180 * M_PI / 180;

  Vector normal = Vector((line_seg_end - line_seg_start).angle() + ninety);
  Vector dir_start_reverse = -dir_start;
  Vector dir_end_reverse = -dir_end;
  float start_incidence = dir_start_reverse.angleBetween(normal);
  float end_incidence = dir_end_reverse.angleBetween(normal);
  if (!dir_start_reverse.isClockWiseOf(normal)) {
    start_incidence = -start_incidence;
  }
  if (!dir_end_reverse.isClockWiseOf(normal)) {
    end_incidence = -end_incidence;
  }

  Vector point;
  Vector line_dir = line_seg_start - line_seg_end;
  line_dir.normalise();
  Vector ray_dir = -normal;
  ray_dir.normalise();
  if (!rayLineIntersection(origin, ray_dir, line_seg_start, line_dir, point)) {
    std::cerr << "Error: Can not reflect, no intersection:" << std::endl;
    std::clog << "  Origin: " << origin << ", ray_dir " << (ray_dir)
        << ", line point " << line_seg_start << ", line dir " << line_dir
        << std::endl;
    return false;
  }

  Vector to_line = point - origin;
  Vector dir_to_line;
  to_line.normalise(dir_to_line);
  Vector reflection_origin = origin + dir_to_line * 2 * (to_line).length();

  Vector reflection_start = dir_end_reverse;
  reflection_start.rotate(-2 * end_incidence);
  Vector reflection_end = dir_start_reverse;
  reflection_end.rotate(-2 * start_incidence);

  Wave* reflection = new Wave(
      reflection_origin,
      reflection_start,
      reflection_end,
      radius,
      waves,
      0);
  waves.push_back(reflection);

  return true;
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
    const Vector& q,
    Vector& out) {
  // Based on Gavin's answer here: https://stackoverflow.com/a/1968345
  Vector s1 = b - a;
  Vector s2 = q - p;

  float ab_parameter, pq_parameter;
  float denominator = -s2.x * s1.y + s1.x * s2.y;
  pq_parameter = (-s1.y * (a.x - p.x) + s1.x * (a.y - p.y)) / denominator;
  ab_parameter = ( s2.x * (a.y - p.y) - s2.y * (a.x - p.x)) / denominator;

  if (ab_parameter >= 0 && ab_parameter <= 1 &&
      pq_parameter >= 0 && pq_parameter <= 1) {
    out = p + pq_parameter * (q - p);
    return true;
  }
  return false;
}

bool Wave::rayLineSegIntersection(
    const Vector& origin,
    const Vector& dir,
    float length,
    const Vector& a,
    const Vector& b,
    Vector& out) {
  Vector radius_ray_end = origin + length * dir;
  return lineSegLineSegIntersection(origin, radius_ray_end, a, b, out);
}

bool Wave::rayLineIntersection(
    const Vector& ray_origin,
    const Vector& ray_dir,
    const Vector& line_point,
    const Vector& line_dir,
    Vector& out) {
  float ray_radius = line_point.y * line_dir.x + line_dir.y * ray_origin.x
      - line_point.x * line_dir.y
      - ray_origin.y * line_dir.x / (ray_dir.y * line_dir.x
      - ray_dir.x * line_dir.y);

  // TODO(jaween): Why does -line_dir give an incorrect result?
  if (ray_radius < 0) {
    //return false;
  }

  float line_parameter = (ray_origin.x + ray_radius * ray_dir.x - line_point.x)
      / line_dir.x;
  out = line_point + line_parameter * line_dir;
  return true;
}

float Wave::getArcLength(const Vector& start, const Vector& end, float radius) {
  return radius * start.angleBetween(end);
}

void Wave::checkIfMovedThroughWall(const Vector& s, const Vector& e) {
  Vector throwaway;
  bool prev_center_intersects = rayLineSegIntersection(origin, center_dir,
      radius - 2 * kSpeed, s, e, throwaway);
  bool center_intersects = rayLineSegIntersection(origin, center_dir,
      radius + 0 * kSpeed, s, e, throwaway);
  if (center_intersects && !prev_center_intersects && age > 1) {
    reflect(origin, start_vector, end_vector, s, e);
    destroy();
  }
}

void Wave::printArc(const Vector& s, const Vector& e) {
  float angle_s = s.angle() * 180 / M_PI;
  float angle_e = e.angle() * 180 / M_PI;
  float spread = s.angleBetween(e) * 180 / M_PI;
  std::clog << " Arc <" << angle_s << ", " << angle_e << ">(spread:"
      << spread << ")" << std::endl;
}

void Wave::destroy() {
  // Marks the wave to be destroyed if the start and end have crossed
  // TODO(jaween): Implement a way to acually destroy a wave from here
  start_vector.set(0, 0);
  end_vector.set(0, 0);
  radius = 0;
  temp_should_destroy = true;
}

bool Wave::tempShouldDestroy() {
  return temp_should_destroy;
}

bool operator==(const Wave& lhs, const Wave& rhs) {
  return (lhs.getOrigin() == rhs.getOrigin())
      && (lhs.getRadius() == rhs.getRadius())
      && (lhs.getStart() == rhs.getStart())
      && (lhs.getEnd() == rhs.getEnd());
}
