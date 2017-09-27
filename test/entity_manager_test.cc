#include "gtest/gtest.h"

#include "entity_manager.h"
#include "kinetic_component.h"
#include "transform_component.h"

TEST(EntityManagerTest, CreateEntity) {
  EntityManager entity_manager;
  EXPECT_EQ(0, entity_manager.createEntity());
}

TEST(EntityManagerTest, CreateEntities) {
  EntityManager entity_manager;
  Entity entity;
  for (uint8_t i = 0; i < 100; i++) {
    entity = entity_manager.createEntity();
  }
  EXPECT_EQ(99, entity);
}

TEST(EntityManagerTest, DeleteEntity) {
  EntityManager entity_manager;
  entity_manager.createEntity();
  Entity entity_to_delete = entity_manager.createEntity();
  entity_manager.createEntity();
  entity_manager.createEntity();
  entity_manager.deleteEntity(entity_to_delete);
  ASSERT_EQ(3, entity_manager.getEntities().size());
  EXPECT_EQ(0, entity_manager.getEntities()[0]);
  EXPECT_EQ(2, entity_manager.getEntities()[1]);
  EXPECT_EQ(3, entity_manager.getEntities()[2]);
}

TEST(EntityManagerTest, GetComponents) {
  EntityManager entity_manager;
  Entity entity = entity_manager.createEntity();
  entity_manager.addComponent<TransformComponent>(entity);
  auto components = entity_manager.getComponents(entity);
  ASSERT_EQ(1, components.size());
}

TEST(EntityManagerTest, RemoveComponents) {
  EntityManager entity_manager;
  Entity entity = entity_manager.createEntity();
  entity_manager.addComponent<TransformComponent>(entity);
  entity_manager.addComponent<TransformComponent>(entity);
  entity_manager.addComponent<KineticComponent>(entity);

  entity_manager.removeComponent<TransformComponent>(entity);

  auto components = entity_manager.getComponents(entity);
  bool found_transform = false;
  bool found_kinetic = false;
  for (const auto& component : components) {
    if (component->typeId() == TransformComponent::getTypeId()) {
      found_transform = true;
    }
    if (component->typeId() == KineticComponent::getTypeId()) {
      found_kinetic = true;
    }
  }
  ASSERT_EQ(found_transform, false);
  ASSERT_EQ(found_kinetic, true);
}
