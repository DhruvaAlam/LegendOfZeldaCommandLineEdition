#include "potion.h"
#include "boardobject.h"
#include "tile.h"

using namespace std;

Potion::Potion(Tile* t, int value): BoardObject{'P',t}{

  int type = this->randNum(1,3);
  int pos = this->randNum(0,1);

  this->atkEffect = 0;
  this->defEffect = 0;
  this->hpEffect = 0;
  int num = this->randNum(1,10); //get number between 1 and 10 to +/-

  if (value == -1){ //randomly generate
    if (type == 1){ //health
      if (pos == 1){
        this->hpEffect += num;
        this->type = "RH";
      } else {
        this->hpEffect -= num;
        this->type = "PH";
      }
    } else if (type == 2){ //tempatk
      if (pos == 1){
        this->atkEffect += 5; //default is 5
        this->type = "BA";
      } else {
        this->atkEffect -= 5;
        this->type = "WA";
      }
    } else { //tempdef
      if (pos == 1){
        this->defEffect += 5;
        this->type = "BD";
      } else {
        this->defEffect -= 5;
        this->type = "WD";
      }
    }
  } else if (value == 0){
    this->hpEffect += num;
    this->type = "RH";
  } else if (value == 1){
    this->atkEffect += 5;
    this->type = "BA";
  } else if (value == 2){
    this->defEffect += 5;
    this->type = "BD";
  } else if (value == 3){
    this->hpEffect -= num;
    this->type = "PH";
  } else if (value == 4){
    this->atkEffect -= 5;
    this->type = "WA";
  } else if (value == 5){
    this->defEffect -= 5;
    this->type = "WD";
  }
}

Potion::~Potion(){}

int Potion::getHpE(){
  return this->hpEffect;
}

int Potion::getAtkE(){
  return this->atkEffect;
}

int Potion::getDefE(){
  return this->defEffect;
}

string Potion::getType() {return this->type;}
