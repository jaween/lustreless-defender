#ifndef PLAYER_SHOOTER_H_
#define PLAYER_SHOOTER_H_

#include "processor.h"
#include "transform.h"

class PlayerShooter : public Processor {
 public:
  PlayerShooter(EntityManager& entity_manager);
  virtual Requirements chooseRequirements() const;
  virtual void update(long ms, const std::set<Entity>& entities);

 private:
  void createBullet(const Transform& entity_transform,
                    const Transform& bullet_transform);
};

#endif // PLAYER_SHOOTER_H_
