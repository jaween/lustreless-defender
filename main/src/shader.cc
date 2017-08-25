#include "SDL_gpu.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>

#include "shader.h"

const std::string Shader::kPositionName = "position";
const std::string Shader::kMvpMatrixName = "mvpMatrix";
const std::string Shader::kModelMatrixName = "model_matrix";

Shader::Shader(std::string vertex_file, std::string fragment_file) {
  uint32_t vertex_shader =
      GPU_LoadShader(GPU_VERTEX_SHADER, vertex_file.c_str());
  std::string message = GPU_GetShaderMessage();
  if (!message.empty()) {
    std::cerr << message << std::endl;
  }

  uint32_t fragment_shader =
      GPU_LoadShader(GPU_FRAGMENT_SHADER, fragment_file.c_str());
  message = GPU_GetShaderMessage();
  if (!message.empty()) {
    std::cerr << message << std::endl;
  }

  program_id = GPU_LinkShaders(vertex_shader, fragment_shader);

  GPU_FreeShader(vertex_shader);
  GPU_FreeShader(fragment_shader);

  mvp_matrix_location =
      GPU_GetUniformLocation(program_id, kMvpMatrixName.c_str());
  model_matrix_location =
    GPU_GetUniformLocation(program_id, kModelMatrixName.c_str());
}

Shader::~Shader() {
  GPU_FreeShader(program_id);
}

void Shader::activate() {
  glUseProgram(program_id);
}

void Shader::deactivate() {
  glUseProgram(0);
}

void Shader::setMvpMatrix(glm::mat4 mvp_matrix) {
  activate();
  GPU_SetUniformMatrixfv(mvp_matrix_location, 1, 4, 4, false,
      glm::value_ptr(mvp_matrix));
  deactivate();
}

// TODO(jaween): Make this setInverseVpMatrix()
void Shader::setModelMatrix(glm::mat4 model_matrix) {
  activate();
  GPU_SetUniformMatrixfv(model_matrix_location, 1, 4, 4, false,
      glm::value_ptr(model_matrix));
  deactivate();
}
