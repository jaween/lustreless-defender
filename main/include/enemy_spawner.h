#ifndef ENEMY_SPAWNER_H_
#define ENEMY_SPAWNER_H_

#include <memory>
#include <string>
#include <vector>

#include "image.h"
#include "processor.h"

class EnemySpawner : public Processor {
 public:
  EnemySpawner(EntityManager& entity_manager);
  virtual void update(long ms);
  void setImageNames(std::vector<std::string> image_names);

 private:
  void spawn();
  uint32_t last_spawn;

  std::vector<std::string> image_names;
};

#endif // ENEMY_SPAWNER_H_

