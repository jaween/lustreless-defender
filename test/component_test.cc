#include "gtest/gtest.h"
#include <memory>

#include "input_component.h"
#include "transform_component.h"

TEST(ComponentTest, PersistentIdClass) {
  ASSERT_NE(TransformComponent::getTypeId(), InputComponent::getTypeId());
  ASSERT_NE(TransformComponent::getTypeId(), InputComponent::getTypeId());
  ASSERT_EQ(TransformComponent::getTypeId(), TransformComponent::getTypeId());
  ASSERT_EQ(InputComponent::getTypeId(), InputComponent::getTypeId());
}

TEST(ComponentTest, PersistentIdInstance) {
  auto p1 = std::shared_ptr<TransformComponent>(new TransformComponent());
  auto p2 = std::shared_ptr<TransformComponent>(new TransformComponent());
  auto p3 = std::shared_ptr<InputComponent>(new InputComponent());

  ASSERT_EQ(p1->getTypeId(), p2->getTypeId());
  ASSERT_NE(p1->getTypeId(), p3->getTypeId());
  ASSERT_NE(p2->getTypeId(), p3->getTypeId());
  ASSERT_EQ(p1->typeId(), p1->getTypeId());
  ASSERT_NE(p2->typeId(), p3->getTypeId());
}
