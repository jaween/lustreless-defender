#version 420 core

uniform mat4 mvpMatrix;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 in_texture_coordinate;

out vec2 texture_coordinate;

void main()
{
  gl_Position = mvpMatrix * vec4(position, 1.0);
  texture_coordinate = in_texture_coordinate;
}

