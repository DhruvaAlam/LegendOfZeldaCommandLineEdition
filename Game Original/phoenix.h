#ifndef __PHOENIX_H__
#define __PHOENIX_H__
#include "enemy.h"

class Tile;

class Phoenix: public Enemy {
public:
  Phoenix(Tile* t);
  ~Phoenix() override;
};

#endif
