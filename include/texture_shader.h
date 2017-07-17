#include "shader.h"

/**
 * Shader which renders a texture onto a piece of geometry.
 */
class TextureShader : public Shader {
 public:
  TextureShader();

 private:
  static const std::string kVertexFile;
  static const std::string kFragmentFile;
};
