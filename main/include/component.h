#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <atomic>
#include <type_traits>

typedef uint32_t ComponentId;

/**
 * Abstract base class from which concrete Components can derive. Each concrete
 * Component type is associated with a unique id when getTypeId<T>() is first
 * called for that particular type.
 */
class Component {
  private:
    static std::atomic<ComponentId> next_id;

  public:
    // Based on the solution given at:
    // https://gpfault.net/posts/mapping-types-to-values.txt.html
    template <typename T>
    static ComponentId getTypeId() {
      static_assert(!std::is_abstract<T>::value,
          "Abstract Components shall not have IDs");
      static ComponentId id = Component::next_id++;
      return id;
    }

    virtual ~Component() = 0;
};

#endif // COMPONENT_H_
