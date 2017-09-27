#include "render_component.h"

RenderComponent::RenderComponent() {
  image = NULL;
}

RenderComponent::~RenderComponent() {
  if (image != NULL) {
    delete image;
  }
}

void RenderComponent::setImage(std::string filename) {
  image = new Image(filename);
}

Image* RenderComponent::getImage() {
  return image;
}
