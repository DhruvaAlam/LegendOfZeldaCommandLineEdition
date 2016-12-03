#include "boardobject.h"
#include "character.h"
#include "enemy.h"
#include "vampire.h"
#include "tile.h"

using namespace std;

Vampire::Vampire(Tile* t): Enemy{'V', t, 50, 25, 25} {}

Vampire::~Vampire() {}
