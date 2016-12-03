#include "boardobject.h"
#include "character.h"
#include "enemy.h"
#include "goblin.h"
#include "tile.h"

using namespace std;

Goblin::Goblin(Tile* t): Enemy{'N', t, 70, 5, 10} {}

Goblin::~Goblin() {}
