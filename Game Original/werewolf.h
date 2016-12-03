#ifndef __WEREWOLF_H__
#define __WEREWOLF_H__
#include "enemy.h"

class Tile;

class WereWolf: public Enemy {
public:
  WereWolf(Tile* t);
  ~WereWolf() override;
};

#endif
