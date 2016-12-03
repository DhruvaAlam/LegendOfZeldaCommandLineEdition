#ifndef __TROLL_H__
#define __TROLL_H__
#include "enemy.h"

class Tile;

class Troll: public Enemy {
public:
  Troll(Tile* t);
  ~Troll() override;
};

#endif
