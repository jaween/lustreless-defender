#include "room.h"
#include "engine.h"

int main() {
  Engine engine;
  Room room(engine);
  engine.run(room);
}
