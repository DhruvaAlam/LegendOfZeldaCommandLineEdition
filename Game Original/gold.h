#ifndef __GOLD_H__
#define __GOLD_H__
#include "boardobject.h"

class Tile;

class Gold: public BoardObject {
	int value;

public:
	Gold(Tile* t, int val = -1); //val can be provided or can be generated
	/*
		val values:
		-1 -> randomly generate
		6 -> normal pile
		7 -> small horde
		8 -> merchant horde
		9 ->dragon horde

	*/
	~Gold() override;
	int getValue();
	bool canPick(); //returns canPick
};

#endif
