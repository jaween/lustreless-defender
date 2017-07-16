#version 420 core

uniform vec4 colour;

out vec4 fragment_colour;

void main()
{
  fragment_colour = colour;
}
