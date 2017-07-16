#ifndef LIGHT_H_
#define LIGHT_H_

#include <vector>

#include "entity.h"
#include "image.h"
#include "occlusion_mask_shader.h"
#include "shadow_map_shader.h"
#include "shadow_mask_shader.h"

/**
 * A coloured 2D light source that can cast shadows off a given set of objects.
 * The source can have different shapes.
 */
class Light : public Entity {
 public:
  Light(SDL_Colour colour);
  ~Light();
  void draw(GPU_Target* gpu_target) override;
  void setObjects(std::vector<Image*> objects);
  void setColour(SDL_Colour colour);
  SDL_Color getColour() const;
  uint16_t getSize() const;
  GLuint getShadowTexture()const;

 private:
  GLuint frame_buffer;
  OcclusionMaskShader* occlusion_mask_shader;
  ShadowMapShader* shadow_map_shader;
  ShadowMaskShader* shadow_mask_shader;
  Image* occlusion_mask;
  Image* shadow_map;
  Image* shadow_mask;
  std::vector<Image*> objects;
  uint16_t size;
  SDL_Colour colour;
  float quality;

  void createOcclusionMask(GPU_Target* gpu_target, std::vector<Image*> images);
  void createShadowMap(GPU_Target* gpu_target);
  void createShadowMask(GPU_Target* gpu_target);
};

#endif // LIGHT_H_
