#include "dwarf.h"
#include "tile.h"
#include "boardobject.h"
#include "character.h"
#include "player.h"
#include "gold.h"

using namespace std;

Dwarf::Dwarf(Tile* tile): Player{tile, 100, 20, 30}{}

Dwarf::~Dwarf(){}

void Dwarf::addGold(Gold* enemyGold){
  double gold = enemyGold->getValue();
  gold *= 2;
  this->numGold = this->numGold + gold;
}

void Dwarf::addGold(double enemyGold){
  enemyGold *= 2;
  this->numGold = this->numGold + enemyGold;
}

char Dwarf::getRace(){return 'd';}
