#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "enemy.h"

class Tile;

class Goblin: public Enemy {
public:
  Goblin(Tile* t);
  ~Goblin() override;
};

#endif
