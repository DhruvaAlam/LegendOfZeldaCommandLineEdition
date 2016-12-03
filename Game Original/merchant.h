#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "enemy.h"

class Player;
class Tile;

class Merchant: public Enemy {
  static bool agro;
public:
  Merchant(Tile* t);
  ~Merchant() override;
  static bool checkAgro();
  static void setAgro(bool b);
  bool isAgro() override; //calls checkAgro to check on static variable
  int defend(Player &p) override; //turns on agro
};

#endif
