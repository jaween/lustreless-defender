#include "gtest/gtest.h"
#include <memory>

#include "kinetic_component.h"
#include "transform_component.h"

TEST(ComponentTest, PersistentIdClass) {
  ASSERT_NE(TransformComponent::getTypeId(), KineticComponent::getTypeId());
  ASSERT_NE(TransformComponent::getTypeId(), KineticComponent::getTypeId());
  ASSERT_EQ(TransformComponent::getTypeId(), TransformComponent::getTypeId());
  ASSERT_EQ(KineticComponent::getTypeId(), KineticComponent::getTypeId());
}

TEST(ComponentTest, PersistentIdInstance) {
  auto p1 = std::shared_ptr<TransformComponent>(new TransformComponent());
  auto p2 = std::shared_ptr<TransformComponent>(new TransformComponent());
  auto p3 = std::shared_ptr<KineticComponent>(new KineticComponent());

  ASSERT_EQ(p1->getTypeId(), p2->getTypeId());
  ASSERT_NE(p1->getTypeId(), p3->getTypeId());
  ASSERT_NE(p2->getTypeId(), p3->getTypeId());
  ASSERT_EQ(p1->typeId(), p1->getTypeId());
  ASSERT_NE(p2->typeId(), p3->getTypeId());
}
