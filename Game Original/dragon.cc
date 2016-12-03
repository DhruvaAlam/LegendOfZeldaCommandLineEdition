#include <cmath>
#include <vector>
#include "dragon.h"
#include "enemy.h"
#include "character.h"
#include "boardobject.h"
#include "player.h"
#include "gold.h"
#include "tile.h"
#include <iostream>
#include <algorithm>

using namespace std;

Dragon::Dragon(Tile* t): Enemy{'D', t, 150, 20, 20}{
}

Dragon::~Dragon(){};

int Dragon::defend(Player &p) {
  int damage = ceil((100.0/(100 + this->def)) * p.getAtk());
  this->hp = this->hp - damage;
  if (this->hp <= 0) {
    (this->tile)->clearTile(); //removes dragon from its tile
  }
  return damage;
}

void Dragon::move() {
  if (this->hp > 0) {
    vector<Tile*> v;
    for (auto &i: *(this->getTile()->getObserverTiles())){
      if (i->getCurChar() == 'G' && (i->getGold())->getValue() == 6) {
        for(auto &j:*(((i->getGold())->getTile())->getObserverTiles())){
          v.emplace_back(j);
        }
      }
    }

    for (auto &i: *(this->getTile()->getObserverTiles())) {
      v.emplace_back(i);
    }
    Tile* playerTile = nullptr;
    for (auto &i: v) {
      if (i->getCurChar() == '@') {
        playerTile = i;
      }
    }
    if (this->isAgro() && playerTile) {
      this->attack(*(playerTile->getPlayer()));
    }
  }
}
