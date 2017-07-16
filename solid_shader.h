#include "SDL.h"

#include "shader.h"

/**
 * Shader which colours a piece of geometry a solid colour.
 */
class SolidShader : public Shader {
 public:
  SolidShader(SDL_Color colour);
  void setColour(SDL_Color colour);

 private:
  static const std::string kVertexFile;
  static const std::string kFragmentFile;
  static const std::string kColourName;

  int colour_location;
};
