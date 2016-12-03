#ifndef __POTION_H__
#define __POTION_H__
#include "boardobject.h"
#include <string>

class Tile;

class Potion: public BoardObject {
	std::string type;
	int hpEffect;
  int atkEffect;
	int defEffect;

public:
	Potion(Tile* t, int value  = -1);
	/*
	value values
	-1 -> random generate potion
	0 -> create restore health
	1 -> create boost attack
	2 -> create boost defence
	3 -> create poison health
	4 -> create wound attack
	5 -> create wound defence
	*/
	~Potion() override;
	int getHpE();
	int getAtkE();
	int getDefE();
	std::string getType(); //returns the type of potion
};

#endif
