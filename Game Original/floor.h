#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <sstream>
#include <vector>
#include <memory>

class Tile;
class Chamber;
class Player;
class TextDisplay;

class Floor {
  int floorNum;
  std::ostream &output;
  int totalnumRows;
  int totalnumCols;

  std::vector<std::vector<Tile*>> grid; //stores all the tiles in 2-D array format
  std::vector<Chamber*> chambers; //stores all the chambers
  TextDisplay* td; //the display
  Player* p; //player's character


public:
  Floor(std::vector<std::string>* gameMap, char character, std::ostream &output);//generate the default map
  ~Floor();
  void init(); //init1, generate random items
  void init(std::vector<std::string>* gameMap); //init2, generate items based on sstream
  void reset(); //clear all BoardObject on the tiles
  int turn(std::string one, std::string two); //parses user input for current turn, then moves all enemies
  /*returns 0 if player has proceed to next floor
  returns 1 if player dies
  returns 2 else
  string two is "move" is player just wants to move */

  /* For the following functions that return int
  0 means move has failed
  1 means move was a success
  2 means player has moved onto a stair

  */
  int floorPotion(std::string dir, std::string *potionName); //use potion in dir
  int attackEnemy(std::string dir, int * damage); // attck enemy in that dir
  int movePlayer(std::string dir); //move player in dir
  void moveEnemies(); //moves all enemies in all chambers
  int randNum(int low, int high);
  void printMap();
  double getPlayerFinalScore();
};

#endif
