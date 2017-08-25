#include "SDL_gpu.h"

#include "solid_shader.h"

const std::string SolidShader::kVertexFile = "main/src/shaders/solid.vert";
const std::string SolidShader::kFragmentFile = "main/src/shaders/solid.frag";
const std::string SolidShader::kColourName = "colour";

SolidShader::SolidShader(SDL_Color colour)
 : Shader(kVertexFile, kFragmentFile) {
  colour_location = GPU_GetUniformLocation(program_id, kColourName.c_str());
  setColour(colour);
}

void SolidShader::setColour(SDL_Color colour) {
  activate();
  float c[4] = {
      colour.r / 255.0f,
      colour.g / 255.0f,
      colour.b / 255.0f,
      colour.a / 255.0f
  };
  GPU_SetUniformfv(colour_location, 4, 1, c);
  deactivate();
}
