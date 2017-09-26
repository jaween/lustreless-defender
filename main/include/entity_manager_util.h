#ifndef ENTITY_MANAGER_UTIL_H_
#define ENTITY_MANAGER_UTIL_H_

#include <boost/functional/hash.hpp>
#include <set>
#include <utility>

#include "component.h"

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

#endif // ENTITY_MANAGER_UTIL_H_
