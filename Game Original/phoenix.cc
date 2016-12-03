#include "boardobject.h"
#include "character.h"
#include "enemy.h"
#include "phoenix.h"
#include "tile.h"

using namespace std;

Phoenix::Phoenix(Tile* t): Enemy{'X', t, 50, 35, 20} {}

Phoenix::~Phoenix() {}
