#version 420 core

uniform sampler2D image;

in vec2 texture_coordinate;

out vec4 fragment_colour;

void main()
{
  fragment_colour = texture(image, texture_coordinate);
}
