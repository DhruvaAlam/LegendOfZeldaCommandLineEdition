#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "character.h"
#include <vector>

class Player;
class Gold;
class Tile;

class Enemy: public Character {

public:
	Enemy(char c, Tile* t, int hp, int atk, int def);
	virtual ~Enemy() = 0;
  virtual bool isAgro(); //returns true as default, merchant and dragon has it's own method
	virtual int defend(Player &p); //when dragon/merchant dies, special actions needs to be executed
	virtual void move(); //enemy moves in a random direction, attacks player if agro
  void attack(Player &p);
};

#endif
