#ifndef __ORC_H__
#define __ORC_H__
#include "player.h"

class Gold;
class Tile;

class Orc: public Player {
public:
  Orc(Tile* tile);
  ~Orc() override;
  void addGold(Gold* enemyGold) override;
  void addGold(double enemyGold) override;
  char getRace() override;
};

#endif
