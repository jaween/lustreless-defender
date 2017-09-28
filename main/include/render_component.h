#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

#include "SDL_gpu.h"
#include <string>
#include <memory>

#include "component.h"
#include "image.h"

class RenderComponent : public Component<RenderComponent> {
 public:
  RenderComponent();
  void setImage(std::string filename);
  std::shared_ptr<Image> getImage();

 private:
  std::shared_ptr<Image> image;
};

#endif // RENDER_COMPONENT_H_
