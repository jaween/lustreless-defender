#version 420 core

const int kMaxLights = 100;
const int kAmbientLight = 0;
const int kPointLight = 1;
const int kSpotLight = 2;
const int kArcLight = 3;

struct Lights
{
  uint count;
  int type[kMaxLights];
  vec2 position[kMaxLights];
  vec3 colour[kMaxLights];
  float intensity[kMaxLights];
  uint size[kMaxLights];
};

uniform sampler2D image;
uniform Lights lights;

in vec2 texture_coordinate;
in vec4 world_position;

out vec4 fragment_colour;

void main() {
  float brightness = 0.1;
  vec4 colour = vec4(1.0);
  // TODO(jaween): Pass in correct worldspace coordinates
  vec2 world_pos2D = vec2(world_position.x, 480 - world_position.y);
  vec4 image_value = texture(image, texture_coordinate);

  for (int i = 0; i < lights.count; i++) {
    int light_type = lights.type[i];
    vec2 light_position = lights.position[i];
    vec3 light_colour = lights.colour[i];
    float light_intensity = lights.intensity[i];
    uint light_size = lights.size[i];

    float dist = distance(world_pos2D.xy, light_position);
    float ratio = 1.0 - dist / (float(light_size) * 0.5f);
    ratio = clamp(ratio, 0, 1);
    brightness += ratio;
    colour += vec4(0.1, 0, 0, 1) * ratio;
  }

  // Multiply blend-mode
  fragment_colour = brightness * colour * image_value;
}
