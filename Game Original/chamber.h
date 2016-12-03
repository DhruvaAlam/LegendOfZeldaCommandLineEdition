#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <vector>

class Tile;
class Enemy;
class Gold;
class Potion;
class Player;

class Chamber {

  std::vector<Tile*> tiles; //this chamber's tiles
  std::vector<Tile*> emptyTiles; //this chamber's empty tiles
  std::vector<Enemy*> enemies; //this chamber's enemies
  int numTiles;
  int numEmptyTiles;
  int chamberNumber;
  void deleteEnemy();

public:
  Chamber(int chamberNumber); //numBoardObj = 0
  ~Chamber();
	int randNum(int low, int high);
  bool isFull(); //checks if chamber is full
  void addTile(Tile *t);
  void addEnemy(); //init1 calls, adds random enemy in a random tile in this chamber
  void addEnemy(Enemy *e); //adds the speicifed enemy to enemy list
  int getChamberNum();

  //only for default maps
  void addGold(); //also spawn a dragon
  void addPotion();
  void addStairs();
  void addPlayer(Player *p);

  void moveEnemies(); //calls all enemy's move method
  void clearChamber(); //clears all its tiles

};

#endif
