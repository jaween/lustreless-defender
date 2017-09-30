#ifndef LIGHT_H_
#define LIGHT_H_

#include <memory>
#include <vector>
#include <unordered_map>

#include "camera.h"
#include "entity_old.h"
#include "image.h"
#include "occlusion_mask_shader.h"
#include "shadow_map_shader.h"
#include "shadow_mask_shader.h"
#include "transform.h"
#include "type_utils.h"

/**
 * A coloured 2D light source that can cast shadows off a given set of objects.
 * The source can have different shapes.
 */
class Light : public EntityOld {
 public:
  Light(SDL_Colour colour, uint16_t size);
  ~Light();
  void draw(GPU_Target* gpu_target) override;
  void draw(
      GPU_Target* gpu_target,
      const Vector& position,
      const std::unordered_map<Transform, std::shared_ptr<Image>>& objects);
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
  Camera* internal_camera;
  uint16_t size;
  SDL_Colour colour;
  float quality;
  float debug_angle;

  void createOcclusionMask(
      GPU_Target* gpu_target,
      const Vector& position,
      const std::unordered_map<Transform, std::shared_ptr<Image>>& objects);
  void createShadowMap(GPU_Target* gpu_target);
  void createShadowMask(GPU_Target* gpu_target);
};

#endif // LIGHT_H_
