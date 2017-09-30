#ifndef HIGHLIGHT_SHADER_H_
#define HIGHLIGHT_SHADER_H_

#include <vector>

#include "light.h"
#include "shader.h"
#include "transform.h"

/**
 * Shader which colours a piece of geometry based on nearby lights in the scene.
 */
class HighlightShader : public Shader {
 public:
  HighlightShader();
  void setLights(
      const std::vector<std::pair<Transform, std::shared_ptr<Light>>>& lights);
  virtual void activate() override;
  virtual void deactivate() override;

 private:
  static const std::string kVertexFile;
  static const std::string kFragmentFile;
  static const std::string kLightCountName;
  static const std::string kLightTypesName;
  static const std::string kLightPositionsName;
  static const std::string kLightColoursName;
  static const std::string kLightSizesName;

  int light_count_location;
  int light_types_location;
  int light_positions_location;
  int light_colours_location;
  int light_sizes_location;
};

#endif // HIGHLIGHT_SHADER_H_
