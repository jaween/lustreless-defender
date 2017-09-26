#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <set>

#include "component.h"
#include "type_utils.h"

class Processor {
 public:
  virtual Requirements chooseRequirements() const = 0;
  virtual void update(long ms, const std::set<Entity>& entities) = 0;
};

#endif // PROCESSOR_H_
