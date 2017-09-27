#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

#include "SDL_gpu.h"
#include <string>

#include "component.h"
#include "image.h"

class RenderComponent : public Component<RenderComponent> {
 public:
  RenderComponent();
  ~RenderComponent();
  void setImage(std::string filename);
  Image* getImage();

 private:
  Image* image;
};

#endif // RENDER_COMPONENT_H_
