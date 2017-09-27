#include "room.h"
#include "engine.h"
#include "entity_manager.h"

int main() {
  EntityManager entity_manager;
  Engine engine(entity_manager);
  Room room(engine, entity_manager);
  engine.run(room);
}
