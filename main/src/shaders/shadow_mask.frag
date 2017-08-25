#version 420

/**
 * Heavily based on:
 * https://github.com/mattdesl/lwjgl-basics/wiki/2D-Pixel-Perfect-Shadows
 */

#define PI 3.14159

uniform sampler1D shadow_map;
uniform vec4 colour;
uniform uint size;

in vec2 texture_coordinate;

out vec4 fragment_colour;

float sampleTexture(float coordinate, float radius) {
  return step(radius, texture(shadow_map, coordinate));
}

void main() {
  vec2 shifted_coordinate = texture_coordinate - vec2(0.5f);
  float angle = atan(shifted_coordinate.y, shifted_coordinate.x);
  float radius = length(texture_coordinate * 2.0f - vec2(1.0f));
  float shadow_map_coordinate = angle / (2 * PI);

  // Shadow gets blurrier the further from the source (using a Gaussian blur)
  float blur = (1 / float(size)) * smoothstep(0.0, 1.0, radius);
  float sum = 0.0;
  sum += sampleTexture(shadow_map_coordinate - 4.0 * blur, radius) * 0.05f;
  sum += sampleTexture(shadow_map_coordinate - 3.0 * blur, radius) * 0.09f;
  sum += sampleTexture(shadow_map_coordinate - 2.0 * blur, radius) * 0.12f;
  sum += sampleTexture(shadow_map_coordinate - 1.0 * blur, radius) * 0.15f;
  sum += sampleTexture(shadow_map_coordinate, radius) * 0.16f;
  sum += sampleTexture(shadow_map_coordinate + 1.0 * blur, radius) * 0.15f;
  sum += sampleTexture(shadow_map_coordinate + 2.0 * blur, radius) * 0.12f;
  sum += sampleTexture(shadow_map_coordinate + 3.0 * blur, radius) * 0.09f;
  sum += sampleTexture(shadow_map_coordinate + 4.0 * blur, radius) * 0.05f;

  // Applies the blur to the alpha channel for soft shadows
  fragment_colour = colour;
  fragment_colour.a *= sum * smoothstep(1.0, 0.0, radius);
}
