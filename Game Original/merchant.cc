#include <cmath>
#include <vector>
#include "merchant.h"
#include "enemy.h"
#include "character.h"
#include "boardobject.h"
#include "player.h"
#include "tile.h"
#include "gold.h"
#include <iostream>

using namespace std;

bool Merchant::agro = false;

Merchant::Merchant(Tile* t): Enemy{'M', t, 30, 75, 5} {}

Merchant::~Merchant(){}

bool Merchant::checkAgro() {
  return agro;
}

void Merchant::setAgro(bool b) {
  agro = b;
}

bool Merchant::isAgro() {
  return checkAgro();
}

int Merchant::defend(Player &p) {
  this->setAgro(true); //all merchants become aggressive
  int damage = ceil((100.0/(100 + this->def)) * p.getAtk());
  this->hp = this->getHp() - damage;
  if (this->hp <= 0) {
    (this->tile)->clearTile(); //removes merchant from its tile
    Gold* g {new Gold ((this->tile), 8)};
    (this->tile)->add(g); //adds Merchant Hoard to current tile
  }
  return damage;
}
