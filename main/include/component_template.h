#ifndef COMPONENT_TEMPLATE_H_
#define COMPONENT_TEMPLATE_H_

#include <type_traits>

#include "component.h"

/**
 * Class from which to inherit from when creating new Components. Each concrete
 * type is associated with a unique id when an instance of that particular type
 * is first constructed. This is an implementation of the Curiously Recurring
 * Template Pattern (CRTP), also known as F-bound polymorphism.
 */
template<class T>
class ComponentTemplate : public Component {
 public:
  // Based on the solution given at:
  // https://gpfault.net/posts/mapping-types-to-values.txt.html
  ComponentTemplate() {
    static_assert(!std::is_abstract<T>::value,
        "Abstract Components shall not have IDs");
    static_assert(std::is_base_of<ComponentTemplate, T>::value,
        "Must be derived from Component");
    static ComponentId id = Component::next_id++;
    ComponentTemplate<T>::id = id;
  }

  ComponentId getTypeId() {
    return id;
  }

 private:
  static ComponentId id;
};

template<class T>
ComponentId ComponentTemplate<T>::id;

#endif // COMPONENT_TEMPLATE_H_
