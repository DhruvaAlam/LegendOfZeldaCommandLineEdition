#include "human.h"
#include "tile.h"
#include "boardobject.h"
#include "character.h"
#include "player.h"
using namespace std;

Human::Human (Tile* tile): Player{tile, 140, 20, 20}{}

Human::~Human(){}

char Human::getRace(){return 'h';}
