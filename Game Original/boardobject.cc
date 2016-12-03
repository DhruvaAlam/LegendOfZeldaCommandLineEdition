#include <memory>
#include <time.h>
#include <cstdlib>
#include "tile.h"
#include "boardobject.h"

using namespace std;

BoardObject::BoardObject(char symbol, Tile* tile): symbol{symbol}, tile{tile}{}

BoardObject::~BoardObject(){}

int BoardObject::randNum(int low, int high){
  int range = high - low + 1;
  //srand(time(NULL));
  int num = rand()%range + low;
  return num;
}

char BoardObject::getChar(){
  return this->symbol;
}

void BoardObject::setTile(Tile *t) {
  this->tile = t;
}

Tile* BoardObject::getTile(){
  return this->tile;
}
