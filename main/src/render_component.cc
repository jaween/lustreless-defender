#include "render_component.h"

RenderComponent::RenderComponent() {
  image = NULL;
}

void RenderComponent::setImage(std::string filename) {
  image = std::shared_ptr<Image>(new Image(filename));
}

std::shared_ptr<Image> RenderComponent::getImage() {
  return image;
}
