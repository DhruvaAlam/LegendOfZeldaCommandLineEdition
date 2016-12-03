#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "enemy.h"

class Gold;
class Player;
class Tile;

class Dragon: public Enemy {
public:
  Dragon(Tile* t);
  ~Dragon() override;
  int defend(Player &p) override;
  void move() override;
};

#endif
