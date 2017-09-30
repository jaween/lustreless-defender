#version 420

#define PI 3.14159

uniform sampler2D occlusion_mask;
uniform uint size;

in vec2 texture_coordinate;

out vec4 fragment_colour;

void main() {
  // Each fragment corresponds to an angle of a ray leaving the light source
  float angle = 2 * PI * texture_coordinate.x;

  // We walk outward from the center of the occlusion mask and save the distance
  // to the first occluder we encounter
  float occluder_distance = 1;
  for (int i = 0; i < size / 2; i++) {
    // Radius here is 0 to 0.5 (to sample from the 1x1 texture)
    float radius = i / float(size);

    vec2 occlusion_mask_coord =
        vec2(0.5f) + vec2(radius * cos(angle), radius * sin(angle));
    vec4 occlusion_mask_sample = texture(occlusion_mask, occlusion_mask_coord);

    // Doubles radius to match unit circle radius of 1
    // This is a hack. Lights don't seem to light the line of pixels at the
    // edges of objects. This extends the light slighty to cover up that issue.
    float extra = 0.005;
    float value = occlusion_mask_sample.r > 0 ? 2 * radius + extra : 1;
    occluder_distance = min(occluder_distance, value);
  }

  // Outputs the distance from the origin to the first occluder for this ray
  fragment_colour = vec4(occluder_distance, occluder_distance,
      occluder_distance, 1.0);
}
