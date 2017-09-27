#ifndef TYPE_UTILS_H_
#define TYPE_UTILS_H_

#include <boost/functional/hash.hpp>
#include <set>
#include <utility>

#include "component.h"

using Entity = uint64_t;
using ComponentPtr = std::shared_ptr<BaseComponent>;
using Requirements = std::set<ComponentId>;

struct SetHasher {
  template<class T>
  std::size_t operator()(const std::set<T>& key) const {
    // TODO: Is this a reasonable way of hashing a set?
    size_t hash = 0;
    for (const T& element : key) {
      boost::hash_combine(hash, element);
    }
    return hash;
  }
};

#endif // TYPE_UTILS_H_
