#version 420

uniform sampler2D image;

in vec2 texture_coordinate;

out vec4 fragment_colour;

void main() {
  vec4 image_value = texture(image, texture_coordinate);
  fragment_colour = image_value;
}
