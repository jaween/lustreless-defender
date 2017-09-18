#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <atomic>

typedef uint32_t ComponentId;

/**
 * Abstract base class for providing unique type IDs to Components. To create a
 * new Component, see ComponentTemplate.
 */
class Component {
 public:
  virtual ComponentId getTypeId() = 0;

 protected:
  static std::atomic<ComponentId> next_id;
};

#endif // COMPONENT_H_
