#include "chamber.h"
#include <vector>
#include "tile.h"
#include "enemy.h"
#include "gold.h"
#include "potion.h"
#include <time.h>
#include <cstdlib>
#include "merchant.h"
#include "dragon.h"
#include "phoenix.h"
#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "troll.h"
#include "stairs.h"
#include "player.h"
#include <iostream>
using namespace std;

Chamber::Chamber(int chamberNumber): numTiles{0},
numEmptyTiles{0}, chamberNumber{chamberNumber}{

}

Chamber::~Chamber(){
  Merchant::setAgro(false);
  this->deleteEnemy();
}

void Chamber::deleteEnemy() {
  for (auto &i: this->enemies) {
    delete i;
  }
}

int Chamber::randNum(int low, int high){
  int range = high - low + 1;
  //srand(time(NULL));
  int num = rand()%range + low;
  return num;
}

bool Chamber::isFull(){
  if (this->numEmptyTiles == 0){
    return true;
  } else {
    return false;
  }
}

void Chamber::addTile(Tile *t){
  this->tiles.emplace_back(t);
  t->addChamber(this->chamberNumber);
  ++(this->numTiles);
  if (t->isEmpty()){
    this->emptyTiles.emplace_back(t);
    ++(this->numEmptyTiles);
  }
}

void Chamber::addEnemy(){
  //choose a random tile
  int pos = randNum(0,this->numEmptyTiles - 1);
  Tile *spawnTile = this->emptyTiles.at(pos);

  int prob = this->randNum(1,18);
  Enemy *newSpawn = nullptr;
  if (prob <= 4){ //spawn a werewolf
    newSpawn = new WereWolf(spawnTile);
  } else if (prob <= 7){ //spawn a vampire
    newSpawn = new Vampire(spawnTile);
  } else if (prob <= 12){ //spawn a goblin
    newSpawn = new Goblin(spawnTile);
  } else if (prob <= 14){ //spawn a troll
    newSpawn = new Troll(spawnTile);
  } else if (prob <= 16){ //spawn a phoenix
    newSpawn = new Phoenix(spawnTile);
  } else { //spawn a merchant
    newSpawn = new Merchant(spawnTile);
  }
  this->addEnemy(newSpawn);
  spawnTile->add(newSpawn);

  //update number of EMpty tiles
  this->emptyTiles.erase(this->emptyTiles.begin()+pos);
  --(this->numEmptyTiles);
}

void Chamber::addPlayer(Player * p){
    int pos = randNum(0,this->numEmptyTiles - 1);
    Tile *spawnTile = this->emptyTiles.at(pos);
    spawnTile->add(p);
    //update number of EMpty tiles
    this->emptyTiles.erase(this->emptyTiles.begin()+pos);
    --(this->numEmptyTiles);


}

void Chamber::addEnemy(Enemy *e){
  this->enemies.emplace_back(e);
}

int Chamber::getChamberNum(){
  return this->chamberNumber;
}

void Chamber::addGold(){
  //choose a random tile
  int pos = randNum(0,this->numEmptyTiles - 1);
  Tile *goldTile = this->emptyTiles.at(pos);
  this->emptyTiles.erase(this->emptyTiles.begin()+pos);
  --this->numEmptyTiles;

  //create gold object
  Gold * gold = new Gold(goldTile);
  goldTile->add(gold);

  if (gold->getValue() == 6){ //spawn a dragon too if needed
    vector<Tile*> *empty = goldTile->getEmptyTiles();
    int size  = (*empty).size();
    int pos2 = randNum(0, size - 1);
    Tile *dragonTile = (*empty).at(pos2);
    Enemy *dragon = new Dragon(dragonTile);
    dragonTile->add(dragon);
    this->enemies.emplace_back(dragon);
  }
}

void Chamber::addPotion(){
  //choose a random tile
  int pos = randNum(0,this->numEmptyTiles - 1);
  Tile *potionTile = this->emptyTiles.at(pos);
  this->emptyTiles.erase(this->emptyTiles.begin()+pos);
  --this->numEmptyTiles;

  Potion *pot = new Potion(potionTile);
  potionTile->add(pot);
}

void Chamber::addStairs(){
  //choose a random tile
  int pos = randNum(0,this->numEmptyTiles - 1);
  Tile *stairTile = this->emptyTiles.at(pos);
  this->emptyTiles.erase(this->emptyTiles.begin()+pos);
  --this->numEmptyTiles;

  Stairs *stairs = new Stairs(stairTile);
  stairTile->add(stairs);

}

void Chamber::moveEnemies(){
  for(auto &i: this->enemies) {
    i->move();
  }
}

void Chamber::clearChamber(){
  for (auto &i: this->tiles) {
    i->clearTile();
  }
  this->deleteEnemy();
  this->emptyTiles = this->tiles;
  this->numEmptyTiles = (this->tiles).size();
  enemies.clear();
}
