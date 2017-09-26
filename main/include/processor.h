#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <set>

#include "component.h"

class Processor {
 public:
  virtual std::set<ComponentId> registerInterest() const = 0;
  virtual void update(long ms) = 0;
};

#endif // PROCESSOR_H_
