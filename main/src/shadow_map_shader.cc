#include "SDL_gpu.h"

#include "shadow_map_shader.h"

const std::string ShadowMapShader::kVertexFile =
    "main/src/shaders/transform.vert";
const std::string ShadowMapShader::kFragmentFile =
    "main/src/shaders/shadow_map.frag";
const std::string ShadowMapShader::kSizeName = "size";

ShadowMapShader::ShadowMapShader(uint16_t size)
    : Shader(kVertexFile, kFragmentFile) {
  size_location =
    GPU_GetUniformLocation(program_id, kSizeName.c_str());

  setSize(size);
}

void ShadowMapShader::setOcclusionMask(GLuint texture) {
  activate();
  glBindTexture(GL_TEXTURE_2D, texture);
  deactivate();
}

void ShadowMapShader::setSize(uint16_t size) {
  activate();
  GPU_SetUniformui(size_location, size);
  deactivate();
}
