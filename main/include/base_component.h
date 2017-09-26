#ifndef BASE_COMPONENT_H_
#define BASE_COMPONENT_H_

#include <atomic>

typedef uint32_t ComponentId;

/**
 * Base class for providing unique type IDs to Components. To create a new
 * Component, see the Component class.
 */
class BaseComponent {
 public:
  virtual ComponentId typeId() = 0;

 protected:
  static std::atomic<ComponentId> next_id;
};

#endif // BASE_COMPONENT_H_
