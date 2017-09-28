#include <algorithm>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

#include "light.h"

Light::Light(SDL_Color colour, uint16_t size) {
  // TODO(jaween): Figure out how to get light sizes to be larger than screen
  this->size = std::min(size, (uint16_t) 400);

  // TODO(jaween): Figure out why perimeter of object is not fully lit
  quality = 1;

  occlusion_mask = new Image(size, size);
  shadow_map = new Image(size * quality, 1);
  shadow_mask = new Image(size, size);
  shadow_mask->setBlendMode(GL_SRC_ALPHA, GL_ONE);

  occlusion_mask_shader = new OcclusionMaskShader();
  shadow_map_shader = new ShadowMapShader(size);
  shadow_mask_shader = new ShadowMaskShader(colour, size);

  // Internal camera is used to position the light source in the center of
  // the viewing area as required by the lighting algorithm
  internal_camera = new Camera(0,0);

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
  debug_angle = 0;
}

Light::~Light() {
  glDeleteFramebuffers(1, &frame_buffer);
  delete occlusion_mask_shader;
  delete shadow_map_shader;
  delete shadow_mask_shader;
  delete occlusion_mask;
  delete shadow_map;
  delete shadow_mask;
  delete internal_camera;
}

void Light::draw(GPU_Target* gpu_target) {
  // Sets up the projection matrix for the camera
  internal_camera->setOrthographic(
      -gpu_target->w/2.0f,
       gpu_target->w/2.0f,
      -gpu_target->h/2.0f,
       gpu_target->h/2.0f);

  createOcclusionMask(gpu_target, objects);
  createShadowMap(gpu_target);
  createShadowMask(gpu_target);

  // Draws the texture with additive blending to mimic additive lighting
  shadow_mask->setBlendingEnabled(true);
  shadow_mask->draw(gpu_target, position.x, position.y);
  debug_angle += 0.01f;
}

void Light::draw(GPU_Target* gpu_target, const Vector& position) {
  this->position = position;
  draw(gpu_target);
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

  // Centers the camera on the light
  Vector camera_position = internal_camera->getPosition();
  internal_camera->setPosition(camera_position + position);

  // Drawing occluders onto mask
  GPU_ClearRGBA(gpu_target, 1, 0, 1, 1);
  for (unsigned int i = 0; i < images.size(); i++) {
    Image* image = objects.at(i);
    float x = 0;
    float y = 0;

    image->setBlendingEnabled(true);
    image->setBlendMode(GL_SRC_ALPHA, GL_ONE);
    image->draw(gpu_target, x, y, debug_angle, occlusion_mask_shader, internal_camera);
    image->setBlendingEnabled(false);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::createShadowMap(GPU_Target* gpu_target) {
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
  glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_1D,
      shadow_map->getTexture(), 0);

  // Centers the camera on the origin
  float width = (float) shadow_map->getWidth();
  float height = (float) shadow_map->getHeight();
  internal_camera->setPosition(Vector(
        gpu_target->w/2.0 - width/2.0,
      -(gpu_target->h/2.0 - height/2.0)));

  shadow_map_shader->setOcclusionMask(occlusion_mask->getTexture());
  shadow_map->draw(gpu_target, 0, 0, 0, shadow_map_shader, internal_camera,
      false);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::createShadowMask(GPU_Target* gpu_target) {
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      shadow_mask->getTexture(), 0);

  // Centers the camera on the origin
  internal_camera->setPosition(
      Vector(gpu_target->w/2 - size/2, -(gpu_target->h/2 - size/2)));

  shadow_mask->setBlendingEnabled(false);
  shadow_mask_shader->setShadowMap(shadow_map->getTexture());
  shadow_mask->draw(gpu_target, 0, 0, 0, shadow_mask_shader, internal_camera,
      false);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
