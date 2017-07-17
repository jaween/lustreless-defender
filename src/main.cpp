#include "room.h"
#include "engine.h"

int main() {
  Room room;
  Engine engine(room);
  engine.run();
}
