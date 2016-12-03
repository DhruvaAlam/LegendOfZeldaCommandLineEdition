#include "gold.h"
#include "boardobject.h"
#include "tile.h"
#include "dragon.h"

using namespace std;

Gold::Gold(Tile* t, int val): BoardObject{'G',t}{
  if (val == -1){ //generate value
    int type = this->randNum(1,8);
    if (type <= 5){ //normal 1,2,3,4,5 = 5/8
      this->value = 1;
    } else if (type <= 7){ //small 6,7 = 2/8
      this->value = 2;
    } else { //dragon 8 = 1/8
      this->value = 6;
    }
  } else if (val == 6) { //normal
    this->value = 1;
  } else if (val == 7){ //small
    this->value = 2;
  } else if (val == 8){ // merchant
    this->value = 4;
  } else { //val ==9 //dragon
    this->value = 6;
  }
}

Gold::~Gold(){}

int Gold::getValue(){
  return this->value;
}

bool Gold::canPick(){
  if (this->value == 6) {
    for (auto &i: *((this->getTile()->getObserverTiles()))){
      if (i->getCurChar() == 'D') {
        return false;
      }
    }
  }
  return true;
}
