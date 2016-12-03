#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "boardobject.h"

class Tile;

class Character: public BoardObject {
	protected:
		int hp;
		int atk;
		int def;

	public:
		Character(char symbol, Tile* tile, int hp, int atk, int def);
		virtual ~Character() = 0;
		int getHp();
		virtual int getAtk();
		virtual int getDef();
};

#endif
