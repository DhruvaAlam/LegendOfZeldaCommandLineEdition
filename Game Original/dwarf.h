#ifndef __DWARF_H__
#define __DWARF_H__
#include "player.h"

class Gold;
class Tile;

class Dwarf: public Player {
public:
  Dwarf(Tile* tile);
  ~Dwarf() override;
  void addGold(Gold* enemyGold) override;
  void addGold(double enemyGold) override;
  char getRace() override;
};

#endif
