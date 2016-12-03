#include "elf.h"
#include "tile.h"
#include "boardobject.h"
#include "character.h"
#include "player.h"
#include "potion.h"

using namespace std;

Elf::Elf(Tile* tile): Player{tile, 140, 30, 10}{}

Elf::~Elf(){}

void Elf::usePotion(Potion* p){
  int hpBuff = p->getHpE();
  int atkBuff = p->getAtkE();
  int defBuff = p->getDefE();
  if (hpBuff < 0){
    hpBuff *= -1;
  }
  if (atkBuff < 0){
    atkBuff *= -1;
  }

  if (defBuff < 0){
    defBuff *= -1;
  }
  if (this->hp + hpBuff > this->maxHp) {
    this->hp = this->maxHp;
  } else {
    this->hp += hpBuff;
  }
  this->tempAtk += atkBuff;
  this->tempDef += defBuff;
  (p->getTile())->clearTile();
}

char Elf::getRace(){return 'e';}
