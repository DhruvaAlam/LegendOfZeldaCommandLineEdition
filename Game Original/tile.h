#ifndef __TILE_H__
#define __TILE_H__
#include <vector>
#include "observer.h"

class Tile;
class TextDisplay;
class BoardObject;
class Gold;
class Chamber;
class Potion;
class Enemy;
class Player;
class Stairs;

class Tile: public Observer {
	const char baseSymbol;
	char currentSymbol;
	const int row;
	const int col;
	bool owned; //owned by a chamber or not
	bool empty; //if tile has anything on it

	int chamberNum; //defaults to -1 if not owned

	Stairs* stairs; //the stairs is on the tile
	Potion* potion; //a potion is on the tile
	Gold* gold; //a gold is on the tile
	Enemy* enemy; //a enemy is on the tile
	Player* player; //the player that is on the tile

	//update these when tile changes
  TextDisplay* observerDisplay; //TextDisplay
	std::vector<Tile*> observerTiles; //Tiles surrounding this tile
	std::vector<Tile*> emptyTiles; //possible moves for enemies

public:
	Tile(char c, int row, int col); //set default symbol and coordinates and TextDisplay
  ~Tile() override;
  void attach(Tile* t); //adds Tile as it's neighbour
	void attach(TextDisplay* td);
  void notify(Tile* t) override; //neighbour notify this tile it has been changed
  void notifyNeigh(); //notify this tiles neighbours it has been changed: TextDisplay and Neighbouring Tiles
  void clearTile(); //removes the BoardObject on this tile

  void add(Potion* p); //adds a potion to this tile
	void add(Gold* g); //adds a gold to this tile
	void add(Enemy* e); //adds a enemy to this tile
	void add(Player* p); //adds a player to this tile
	void add(Stairs* s); //adds the stairs to this tile

	void addChamber(int n); //adds the chamber number it belongs to

  bool canStepP(); //Can Player step on here? Player can step on Gold!
  bool canStepE(); //Can Enemy step on here?

	bool isOwned(); //checks if it belongs to a chamber, for initializing board
	bool isEmpty(); // checks if there is an object on this tile
	char getCurChar(); //returns the current char

	int getRow(); //returns row co-ord
	int getCol(); //return col co-ord
	int getChamberNum(); //returns the chamberNum

	Potion* getPotion(); //returns the potion pointer
	Gold* getGold(); //returns the gold pointer
	Enemy* getEnemy(); //returns the enemy pointer
	Player* getPlayer(); //returns the Player pointer

	std::vector<Tile*>* getEmptyTiles();
	std::vector<Tile*>* getObserverTiles();

	void addChamberNum(int cn);
	void chamberRippleEffect(int cn);

};

#endif
