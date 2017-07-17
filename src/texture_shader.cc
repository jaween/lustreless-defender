#include "GL/glew.h"

#include "texture_shader.h"

const std::string TextureShader::kVertexFile = "src/shaders/transform.vert";
const std::string TextureShader::kFragmentFile = "src/shaders/texture.frag";

TextureShader::TextureShader()
  : Shader(kVertexFile, kFragmentFile) {
}
