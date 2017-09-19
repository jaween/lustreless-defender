#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <type_traits>

#include "base_component.h"

/**
 * Class from which to inherit from when creating new Components. This is an
 * implementation of the Curiously Recurring Template Pattern (CRTP), also known
 * as F-bound polymorphism.Each concrete type is associated with a unique id
 * when an instance of that particular type is first constructed or when the
 * getTypeId() function is first called.
 */
template<class T>
class Component : public BaseComponent {
 public:
  // Based on the solution given at:
  // https://gpfault.net/posts/mapping-types-to-values.txt.html
  Component() {
    static_assert(!std::is_abstract<T>::value,
        "Abstract Components shall not have IDs");
    static_assert(std::is_base_of<Component, T>::value,
        "Must be derived from Component");

    // Locks down the Component's type ID if it hasn't already been set
    getTypeId();
  }

  static ComponentId getTypeId() {
    static ComponentId id = next_id++;
    Component::id = id;
    return Component::id;
  }

  ComponentId typeId() {
    return getTypeId();
  }

 private:
  static ComponentId id;
};

template<class T>
ComponentId Component<T>::id;

#endif // COMPONENT_H_
