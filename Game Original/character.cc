#include "character.h"
#include "boardobject.h"
#include "tile.h"

using namespace std;

Character::Character(char symbol, Tile* tile, int hp, int atk,
   int def): BoardObject{symbol, tile}, hp{hp}, atk{atk}, def{def} {}

Character::~Character(){}

int Character::getHp(){
  return this->hp;
}

int Character::getAtk(){
  return this->atk;
}

int Character::getDef(){
  return this->def;
}
