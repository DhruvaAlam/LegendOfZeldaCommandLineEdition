#include "boardobject.h"
#include "character.h"
#include "enemy.h"
#include "tile.h"
#include "player.h"
#include "gold.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

Enemy::Enemy(char symbol, Tile* t, int hp, int atk, int def)
: Character{symbol, t, hp, atk, def}{}

Enemy::~Enemy(){}

bool Enemy::isAgro() {return true;};

int Enemy::defend(Player &p) {
  int damage = ceil((100.0/(100 + this->def)) * p.getAtk());
  this->hp = this->hp - damage;
  if (this->hp <= 0) {
    (this->tile)->clearTile(); //removes Enemy from tile
    p.addGold(1.0); // adds one gold to player
  }
  return damage;
}

void Enemy::attack(Player &p){
  int chance = randNum(1,2);
  if (chance == 1){
    p.defend(*this);
  }
}

void Enemy::move(){
  if (this->hp > 0) {
    vector<Tile*> emptyTiles = *((this->tile)->getEmptyTiles()); //gets a list of possible moves for enemy
    Tile* playerTile = nullptr;
    for (auto &i: *(this->getTile()->getObserverTiles())) {
      if (i->getCurChar() == '@') {
        playerTile = i;
      }
    }
    if (this->isAgro() && playerTile != nullptr) {
      this->attack(*(playerTile->getPlayer()));
    } else if (emptyTiles.size() > 1) {
      int a = this->randNum(0, emptyTiles.size() - 1);
      (this->tile)->clearTile(); //removes Enemy from current tile
      (emptyTiles.at(a))->add(this); //adds Enemy to tile
    } else if (emptyTiles.size() == 1) {
      (this->tile)->clearTile(); //removes Enemy from current tile
      (emptyTiles.at(0))->add(this); //adds Enemy to tile
    }
  }
}
