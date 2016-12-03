#include "boardobject.h"
#include "character.h"
#include "enemy.h"
#include "troll.h"
#include "tile.h"

using namespace std;

Troll::Troll(Tile* t): Enemy{'T', t, 120, 25, 15} {}

Troll::~Troll() {}
