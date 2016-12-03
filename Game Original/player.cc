#include "player.h"
#include "boardobject.h"
#include "character.h"
#include "potion.h"
#include "gold.h"
#include "enemy.h"
#include "tile.h"
#include <cmath>
#include <iostream>

using namespace std;

Player::Player(Tile* tile, int hp, int atk, int def): Character{'@', tile, hp, atk, def},
  numGold{0}, tempAtk{0}, tempDef{0}, maxHp{hp}{}

Player::~Player(){}

void Player::addGold(Gold* g){
  this->numGold += g->getValue();
}

void Player::addGold(double g){
  this->numGold += g;
}

void Player::usePotion(Potion* pot){
  int hpChange = pot->getHpE();
  int atkChange = pot->getAtkE();
  int defChange = pot->getDefE();
  if (this->hp <= hpChange * -1){
    this->hp = 1;
  } else if (this->hp + hpChange > this->maxHp) {
    this->hp = this->maxHp;
  } else {
    this->hp += hpChange;
  }
  this->tempAtk += atkChange;
  this->tempDef += defChange;
  (pot->getTile())->clearTile();

}

int Player::attack(Enemy &e){
  return e.defend(*this);
}

void Player::defend(Enemy &e){
  int damage = ceil((100.0/(100 + this->getDef())) * e.getAtk());
  this->hp -= damage;
}

double Player::getGold(){
  return this->numGold;
}

int Player::getHp(){
  return this->hp;
}

int Player::getAtk(){
  int atk = this->tempAtk + this->atk;
  if (atk < 0) {
    return 0;
  }
  return atk;
}

int Player::getDef(){
  int def = this->tempDef + this->def;
  if (def < 0) {
    return 0;
  }
  return def;
}

void Player::resetTemp(){
  this->tempDef = 0;
  this->tempAtk = 0;
}
