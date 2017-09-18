#include "gtest/gtest.h"
#include <memory>

#include "transform_component.h"

TEST(ComponentTest, PersistentId) {
  auto p1 = std::shared_ptr<TransformComponent>(new TransformComponent());
  auto p2 = std::shared_ptr<TransformComponent>(new TransformComponent());
  ASSERT_EQ(p1->getTypeId(), p2->getTypeId());
}
