#ifndef SHADER_H_
#define SHADER_H_

#include "GL/glew.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>

/**
 * Base implementation for an OpenGL GPU shader with mostly generic
 * functionality.
 */
class Shader {
 public:
  Shader(std::string vertex_file, std::string fragment_file);
  ~Shader();
  virtual void activate();
  virtual void deactivate();
  void setMvpMatrix(glm::mat4 mvp_matrix);
  void setModelMatrix(glm::mat4 model_matrix);

 private:
  static const std::string kPositionName;
  static const std::string kMvpMatrixName;
  static const std::string kModelMatrixName;

  GLint position_location;
  GLint mvp_matrix_location;
  GLint model_matrix_location;

 protected:
  uint32_t program_id;
};

#endif // SHADER_H_
