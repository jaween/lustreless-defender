#include "highlight_shader.h"

const std::string HighlightShader::kVertexFile = "src/shaders/highlight.vert";
const std::string HighlightShader::kFragmentFile = "src/shaders/highlight.frag";
const std::string HighlightShader::kLightCountName = "lights.count";
const std::string HighlightShader::kLightTypesName = "lights.type";
const std::string HighlightShader::kLightPositionsName = "lights.position";
const std::string HighlightShader::kLightColoursName = "lights.colour";
const std::string HighlightShader::kLightSizesName = "lights.size";

HighlightShader::HighlightShader()
 : Shader(kVertexFile, kFragmentFile) {
  light_count_location =
      GPU_GetUniformLocation(program_id, kLightCountName.c_str());
  light_types_location =
      GPU_GetUniformLocation(program_id, kLightTypesName.c_str());
  light_positions_location =
      GPU_GetUniformLocation(program_id, kLightPositionsName.c_str());
  light_colours_location =
      GPU_GetUniformLocation(program_id, kLightColoursName.c_str());
  light_sizes_location =
      GPU_GetUniformLocation(program_id, kLightSizesName.c_str());
}

void HighlightShader::setLights(std::vector<Light*> lights) {
  activate();

  GPU_SetUniformui(light_count_location, lights.size());

  unsigned int types[lights.size()];
  float positions[lights.size() * 2];
  unsigned int sizes[lights.size()];
  float colours[lights.size() * 3];
  for (int i = 0; i < lights.size(); i++) {
    SDL_Color colour = lights.at(i)->getColour();
    types[i] = 1;
    positions[i * 2 + 0] = lights.at(i)->getPosition().x;
    positions[i * 2 + 1] = lights.at(i)->getPosition().y;
    colours[i * 3 + 0] = colour.r / 255.0f;
    colours[i * 3 + 1] = colour.g / 255.0f;
    colours[i * 3 + 2] = colour.b / 255.0f;
    sizes[i] = lights.at(i)->getSize();
  }

  for (int i = 0; i < lights.size(); i++) {
    GPU_SetUniformuiv(light_types_location, 1, lights.size(), types);
    GPU_SetUniformfv(light_positions_location, 2, lights.size(), positions);
    GPU_SetUniformuiv(light_sizes_location, 1, lights.size(), sizes);
    GPU_SetUniformfv(light_colours_location, 3, lights.size(), colours);
  }

  deactivate();
}

void HighlightShader::activate() {
  Shader::activate();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void HighlightShader::deactivate() {
  Shader::deactivate();
  glDisable(GL_BLEND);
}
