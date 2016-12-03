#ifndef __STAIRS_H__
#define __STAIRS_H__
#include "boardobject.h"

class Tile;

class Stairs: public BoardObject {
public:
	Stairs(Tile* t);
	~Stairs();
};

#endif
