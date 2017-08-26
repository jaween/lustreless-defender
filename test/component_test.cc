#include "gtest/gtest.h"

#include "transform_component.h"

TEST(ComponentTest, PersistentId) {
  ComponentId id = Component::getTypeId<TransformComponent>();
  ASSERT_EQ(id, Component::getTypeId<TransformComponent>());
}
