#ifndef __ELF_H__
#define __ELF_H__
#include "player.h"

class Potion;
class Tile;

class Elf: public Player {
public:
  Elf(Tile* tile);
  ~Elf() override;
  void usePotion(Potion* p) override;
  char getRace() override;
};

#endif
