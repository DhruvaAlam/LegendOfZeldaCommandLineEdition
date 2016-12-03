#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

class Tile;

class Human: public Player {
public:
  Human(Tile* tile);
  ~Human() override;
  char getRace() override;
};

#endif
