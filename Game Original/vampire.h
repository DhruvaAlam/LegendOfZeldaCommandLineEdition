#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "enemy.h"

class Tile;

class Vampire: public Enemy {
public:
  Vampire(Tile* t);
  ~Vampire() override;
};

#endif
