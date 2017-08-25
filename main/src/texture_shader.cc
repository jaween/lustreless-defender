#include "GL/glew.h"

#include "texture_shader.h"

const std::string TextureShader::kVertexFile =
    "main/src/shaders/transform.vert";
const std::string TextureShader::kFragmentFile =
    "main/src/shaders/texture.frag";

TextureShader::TextureShader()
  : Shader(kVertexFile, kFragmentFile) {
}
