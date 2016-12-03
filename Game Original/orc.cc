#include "orc.h"
#include "tile.h"
#include "boardobject.h"
#include "character.h"
#include "player.h"
#include "gold.h"

using namespace std;

Orc::Orc (Tile* tile): Player{tile, 180, 30, 25}{}

Orc::~Orc(){}

void Orc::addGold(Gold* enemyGold){
  double gold = enemyGold->getValue();
  gold *= 0.5;
  this->numGold = this->numGold + gold;
}

void Orc::addGold(double enemyGold){
  enemyGold *= 0.5;
  this->numGold = this->numGold + enemyGold;
}

char Orc::getRace(){return 'o';}
