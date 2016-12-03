#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "character.h"

class Gold;
class Potion;
class Enemy;
class Tile;

class Player: public Character {
protected:
  double numGold;
  int tempAtk;
  int tempDef;
  int maxHp;
public:
  Player(Tile* tile, int hp, int atk, int def);
  virtual ~Player() = 0;
  virtual void addGold(Gold* g);
  virtual void addGold(double g);
  virtual void usePotion(Potion* p);
  virtual int attack(Enemy &e);
  //returns the damage dealt to the Enemy
  virtual void defend(Enemy &e);
  double getGold();
  int getHp();
  int getAtk() override; //returns atk + tempatk
  int getDef() override; //returns def + tempdef
  void resetTemp();
  virtual char getRace() = 0;
};

#endif
