#ifndef SHADOW_MASK_SHADER_H_
#define SHADOW_MASK_SHADER_H_

#include "GL/glew.h"
#include "SDL_gpu.h"

#include "shader.h"

/**
 * Creates a coloured, semi-transparent mask representing pixels that are in
 * shadow and pixels that are in light based on a given shadow map. The
 * resulting shadow masks look the best when drawn with additive blending (to
 * mimic additive lighting).
 */
class ShadowMaskShader : public Shader {
 public:
  ShadowMaskShader(SDL_Color colour, uint16_t size = 256);
  void setShadowMap(GLuint texture);
  void setColour(SDL_Color colour);
  void setSize(uint16_t size);

 private:
  static const std::string kVertexFile;
  static const std::string kFragmentFile;

  static const std::string kColourName;
  static const std::string kSizeName;

  GLuint colour_location;
  GLuint size_location;
};

#endif // SHADOW_MASK_SHADER_H_
