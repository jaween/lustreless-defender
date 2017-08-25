#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"

#include "image.h"

Image::Image(uint32_t width, uint32_t height) {
  init();
  this->width = width;
  this->height = height;

  setTextureData(width, height, NULL);
}

Image::Image(std::string filename) {
  init();

  int w, h, components;
  uint8_t* texture_data =
      stbi_load(filename.c_str(), &w, &h, &components, STBI_rgb_alpha);
  width = w;
  height = h;

  setTextureData(width, height, texture_data);
}

Image::~Image() {
  glDeleteTextures(1, &texture);
  glDeleteBuffers(1, &uv_buffer);
  glDeleteBuffers(1, &index_buffer);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteVertexArrays(1, &vertex_array);
  delete default_camera;
}

void Image::draw(GPU_Target* gpu_target, float x, float y, Shader* shader,
    Camera* camera, bool bind_texture) {
  drawInternal(gpu_target, x, y, width, height, shader, camera, bind_texture);
}

void Image::draw(GPU_Target* gpu_target, float x, float y, uint32_t width,
    uint32_t height, Shader* shader, Camera* camera,
    bool bind_texture) {
  drawInternal(gpu_target, x, y, width, height, shader, camera, bind_texture);
}

GLuint Image::getTexture() {
  return texture;
}

uint32_t Image::getWidth() const {
  return width;
}

uint32_t Image::getHeight() const {
  return height;
}

void Image::init() {
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  float vertices[] = {
     -0.500f,  0.500f, 0.0f, // Top left
     -0.500f, -0.500f, 0.0f, // Bottom left
      0.500f,  0.500f, 0.0f, // Top right
      0.500f, -0.500f, 0.0f, // Bottom right
  };

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices,
      GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  uint32_t indices[] = { 0, 1, 3, 0, 3, 2 };

  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices,
      GL_STATIC_DRAW);

  float uvs[] = {
      0.0f, 1.0f, // Top left
      0.0f, 0.0f, // Bottom left
      1.0f, 1.0f, // Top right
      1.0f, 0.0f, // Bottom right
  };

  glGenBuffers(1, &uv_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), uvs,
      GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  default_camera = new Camera(0, 0);
}

void Image::setTextureData(uint32_t width, uint32_t height, uint8_t* data) {
  texture_target = height > 1 ? GL_TEXTURE_2D : GL_TEXTURE_1D;

  glGenTextures(1, &texture);
  glBindTexture(texture_target, texture);

  if (texture_target == GL_TEXTURE_2D) {
    glTexImage2D(texture_target, 0, GL_RGBA, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
  } else {
    glTexImage1D(texture_target, 0, GL_RGBA, width, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
  }

  glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  float colour[] = { 1, 1, 0, 1 };
  glTexParameterfv(texture_target, GL_TEXTURE_BORDER_COLOR, colour);
  // TODO(jaween): Why do these properties mess up the shadows?
  /*glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);*/
}

void Image::drawInternal(GPU_Target* gpu_target, float x, float y,
    uint32_t width, uint32_t height, Shader* shader, Camera* camera,
    bool bind_texture) {
  Shader* image_shader = shader == NULL ? &texture_shader : shader;
  Camera* image_camera = camera == NULL ? default_camera : camera;
  if (camera == NULL) {
    image_camera->setOrthographic(gpu_target->w, gpu_target->h);
  }

  glm::mat4 view_projection_matrix = image_camera->getViewProjectionMatrix();
  glm::mat4 model_matrix = glm::translate(glm::mat4(),
      glm::vec3(x, -y, 0.0f));
  model_matrix = glm::scale(model_matrix,
      glm::vec3((float) width, (float) height, 1.0f));
  image_shader->setModelMatrix(model_matrix);
  image_shader->setMvpMatrix(view_projection_matrix * model_matrix);

  const int index_count = 6;
  image_shader->activate();
  if (bind_texture) {
    glBindTexture(texture_target, texture);
  }
  glBindVertexArray(vertex_array);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
  image_shader->deactivate();
}
