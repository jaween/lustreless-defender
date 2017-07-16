#include "shadow_mask_shader.h"

const std::string ShadowMaskShader::kVertexFile =
    "src/shaders/transform.vert";
const std::string ShadowMaskShader::kFragmentFile =
    "src/shaders/shadow_mask.frag";
const std::string ShadowMaskShader::kColourName = "colour";
const std::string ShadowMaskShader::kSizeName = "size";

ShadowMaskShader::ShadowMaskShader(SDL_Colour colour, uint16_t size)
    : Shader(kVertexFile, kFragmentFile) {
  colour_location =
      GPU_GetUniformLocation(program_id, kColourName.c_str());
  size_location =
      GPU_GetUniformLocation(program_id, kSizeName.c_str());

  float matrix[16];
  GPU_MatrixIdentity(matrix);
  GPU_MatrixOrtho(matrix, 0, 640, 480, 0, 0, 1);
  GPU_MatrixTranslate(matrix, 128, 480 - 128, 0.0);
  GPU_MatrixScale(matrix, 256, 256, 0.0);

  setColour(colour);
  setSize(size);
}

void ShadowMaskShader::setShadowMap(GLuint texture) {
  activate();
  glBindTexture(GL_TEXTURE_1D, texture);
  deactivate();
}

void ShadowMaskShader::setColour(SDL_Color colour) {
  float c[4] = {
      colour.r/255.0f,
      colour.g/255.0f,
      colour.b/255.0f,
      colour.a/255.0f };
  activate();
  GPU_SetUniformfv(colour_location, 4, 1, c);
  deactivate();
}

void ShadowMaskShader::setSize(uint16_t size) {
  activate();
  GPU_SetUniformui(size_location, size);
  deactivate();
}
