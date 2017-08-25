#ifndef OCCLUSION_MASK_SHADER_H_
#define OCCLUSION_MASK_SHADER_H_

#include "shader.h"

/**
 * Creates a texture with opaque pixels where there is geometry and transparent
 * pixels where there isn't.
 */
class OcclusionMaskShader : public Shader {
 public:
  OcclusionMaskShader();

 private:
  static const std::string kVertexFile;
  static const std::string kFragmentFile;
};

#endif // OCCLUSION_MASK_SHADER
