#include "boardobject.h"
#include "character.h"
#include "enemy.h"
#include "werewolf.h"
#include "tile.h"

using namespace std;

WereWolf::WereWolf(Tile* t): Enemy{'W', t, 120, 30, 25} {}

WereWolf::~WereWolf() {}
