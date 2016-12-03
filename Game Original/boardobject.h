#ifndef __BOARDOBJECT_H__
#define __BOARDOBJECT_H__

class Tile;

class BoardObject {

protected:
	char symbol;
  Tile* tile;

public:
	BoardObject(char symbol, Tile* t);
	virtual ~BoardObject() = 0;
	int randNum(int, int);
	char getChar();
	void setTile(Tile*);
	Tile* getTile();
};

#endif
