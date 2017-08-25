#ifndef SHADOW_MAP_SHADER_H_
#define SHADOW_MAP_SHADER_H_

#include "GL/glew.h"

#include "shader.h"

/**
 * Writes to a 1D texture indicating the distances to occluders from the center
 * of the occlusion map, which each value along the horizontal axis
 * corresponding to a different angle.
 */
class ShadowMapShader : public Shader {
 public:
  ShadowMapShader(uint16_t size = 256);
  void setOcclusionMask(GLuint texture);
  void setSize(uint16_t size);

 private:
  static const std::string kVertexFile;
  static const std::string kFragmentFile;

  static const std::string kSizeName;

  int size_location;
  int mvp_matrix_location;
};

#endif // SHADOW_MAP_SHADER_H_
