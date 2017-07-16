#include <iostream>

#include "light.h"

Light::Light(SDL_Color colour) {
  // TODO(jaween): Figure out how to get light sizes to be larger than screen
  size = 400;

  // TODO(jaween): Figure out why perimeter of object is not fully lit
  quality = 1;

  occlusion_mask = new Image(size, size);
  shadow_map = new Image(size * quality, 1);
  shadow_mask = new Image(size, size);

  occlusion_mask_shader = new OcclusionMaskShader();
  shadow_map_shader = new ShadowMapShader(size);
  shadow_mask_shader = new ShadowMaskShader(colour, size);

  // Framebuffer is used as a destination for each intermediate stage of
  // lighting
  glGenFramebuffers(1, &frame_buffer);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      occlusion_mask->getTexture(), 0);

  int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Framebuffer is not OK, status is " << status << std::endl;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Light::~Light() {
  glDeleteFramebuffers(1, &frame_buffer);
  delete occlusion_mask_shader;
  delete shadow_map_shader;
  delete shadow_mask_shader;
  delete occlusion_mask;
  delete shadow_map;
  delete shadow_mask;
}

void Light::draw(GPU_Target* gpu_target) {
  createOcclusionMask(gpu_target, objects);
  createShadowMap(gpu_target);
  createShadowMask(gpu_target);
  //occlusion_mask->draw(gpu_target, position.x, position.y);

  // Draws the texture with additive blending to mimic additive lighting
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  shadow_mask->draw(gpu_target, position.x, position.y);
  glDisable(GL_BLEND);
}

void Light::setObjects(std::vector<Image*> objects) {
  this->objects = objects;
}

void Light::setColour(SDL_Color colour) {
  shadow_mask_shader->setColour(colour);
  this->colour = colour;
}

GLuint Light::getShadowTexture() const {
  return shadow_mask->getTexture();
}

SDL_Color Light::getColour() const {
  return colour;
}

uint16_t Light::getSize() const {
  return size;
}

void Light::createOcclusionMask(GPU_Target* gpu_target,
    std::vector<Image*> images) {
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      occlusion_mask->getTexture(), 0);

  float model[16];
  float vp[16];
  float mvp[16];
  GPU_MatrixIdentity(vp);
  GPU_MatrixOrtho(vp, 0, gpu_target->w, 0, gpu_target->h, 0, 1);
  GPU_MatrixTranslate(vp, size/2, -size/2, 0.0f);
  GPU_MatrixTranslate(vp, -position.x, position.y, 0.0);

  // Drawing occluders onto mask
  GPU_ClearRGBA(gpu_target, 0, 0, 0, 0);
  for (int i = 0; i < images.size(); i++) {
    Image* image = objects.at(i);
    float x = 320;
    float y = 240;
    GPU_MatrixIdentity(model);
    GPU_MatrixTranslate(model, x, size-y, 0.0f);
    GPU_MatrixScale(model, image->getWidth(), image->getHeight(), 1.0f);
    GPU_Multiply4x4(mvp, vp, model);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    objects.at(i)->draw(gpu_target, x, y, occlusion_mask_shader, mvp);
    glDisable(GL_BLEND);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::createShadowMap(GPU_Target* gpu_target) {
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
  glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_1D,
      shadow_map->getTexture(), 0);

  float matrix[16];
  GPU_MatrixIdentity(matrix);
  GPU_MatrixOrtho(matrix, 0, gpu_target->w, gpu_target->h, 0, 0, 1);
  GPU_MatrixTranslate(matrix, 0, size, 0.0);
  GPU_MatrixTranslate(matrix, quality * size / 2, size / 2, 0.0);
  GPU_MatrixScale(matrix, quality * size, size, 0.0);

  shadow_map_shader->setOcclusionMask(occlusion_mask->getTexture());
  shadow_map->draw(gpu_target, 0, 0, shadow_map_shader, matrix);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::createShadowMask(GPU_Target* gpu_target) {
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      shadow_mask->getTexture(), 0);

  float matrix[16];
  GPU_MatrixIdentity(matrix);
  GPU_MatrixOrtho(matrix, 0, gpu_target->w, 0, gpu_target->h, 0, 1);
  GPU_MatrixTranslate(matrix, 0, size, 0.0);
  GPU_MatrixTranslate(matrix, size / 2, -size / 2, 0.0);
  GPU_MatrixScale(matrix, size, size, 0.0);

  GPU_ClearRGBA(gpu_target, 0, 0, 0, 0);
  shadow_mask_shader->setShadowMap(shadow_map->getTexture());
  shadow_mask->draw(gpu_target, 0, 0, shadow_mask_shader, matrix);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
