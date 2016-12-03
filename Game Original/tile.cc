#include <vector>
#include "tile.h"
#include "observer.h"
#include "boardobject.h"
#include "chamber.h"
#include "textdisplay.h"
#include "potion.h"
#include "gold.h"
#include "stairs.h"
#include "enemy.h"
#include "character.h"
#include "player.h"
#include <algorithm>

using namespace std;

Tile::Tile(char c, int row, int col): baseSymbol{c}, row{row}, col{col} {
  this->currentSymbol = c;
  if (c == '.') {
    this->owned = false;
    this->empty = true;
  } else {
    this->owned = true;
    this->empty = false;
  }
  this->chamberNum = -1;
  this->stairs = nullptr;
  this->potion = nullptr;
  this->gold = nullptr;
  this->enemy = nullptr;
  this->player = nullptr;
  this->observerDisplay = nullptr;
}

Tile::~Tile(){
  delete this->stairs;
  delete this->potion;
  delete this->gold;
};

void Tile::attach(Tile* t) {
  (this->observerTiles).emplace_back(t);
  if (t->isEmpty()) {
    (this->emptyTiles).emplace_back(t);
  }
}

void Tile::attach(TextDisplay* td) {
  this->observerDisplay = td;
}

void Tile::notify(Tile* t) {
  if (t->isEmpty()) {
    (this->emptyTiles).emplace_back(t);
    sort((this->emptyTiles).begin(), (this->emptyTiles).end());
    unique((this->emptyTiles).begin(), (this->emptyTiles).end()); //makes sure there's no dupes
  } else {
    emptyTiles.erase(remove((this->emptyTiles).begin(), (this->emptyTiles).end(), t),(this->emptyTiles).end());
  }
}

void Tile::notifyNeigh(){
  for (auto &i: this->observerTiles) {
    i->notify(this);
  }
  (this->observerDisplay)->notify(this);
}

void Tile::clearTile(){
  this->currentSymbol = this->baseSymbol;
  if (this->baseSymbol == '.'){
    this->empty = true;
  }
  delete this->stairs;
  this->stairs = nullptr;
  delete this->potion;
  this->potion = nullptr;
  delete this->gold;
  this->gold = nullptr;

  this->enemy = nullptr;
  this->player = nullptr;
  this->notifyNeigh();
}

void Tile::add(Potion* p) {
  this->clearTile();
  p->setTile(this);
  this->currentSymbol = p->getChar();
  this->empty = false;
  this->potion = p;
  this->notifyNeigh();
}

void Tile::add(Gold* g) {
  this->clearTile();
  g->setTile(this);
  this->currentSymbol = g->getChar();
  this->empty = false;
  this->gold = g;
  this->notifyNeigh();
}

void Tile::add(Enemy* e) {
  this->clearTile();
  e->setTile(this);
  this->currentSymbol = e->getChar();
  this->empty = false;
  this->enemy = e;
  this->notifyNeigh();
}

void Tile::add(Player* p) {
  if (gold != nullptr && gold->canPick()) {
    p->addGold(this->gold);
    delete this->gold;
    this->gold = nullptr;
  }
  this->clearTile();
  p->setTile(this);
  this->currentSymbol = p->getChar();
  this->empty = false;
  this->player = p;
  this->notifyNeigh();
}

void Tile::add(Stairs* s) {
  this->clearTile();
  s->setTile(this);
  this->currentSymbol = s->getChar();
  this->empty = false;
  this->stairs = s;
  this->notifyNeigh();
}

void Tile::addChamber(int n) {
  this->owned = true;
  this->chamberNum = n;
}

bool Tile::canStepP(){
  if (this->potion == nullptr && this->enemy == nullptr) {
    if (this->gold != nullptr && !(gold->canPick())) {
      return false;
    } else if (this->baseSymbol == '.' || this->baseSymbol == '+'
    || this->baseSymbol == '#') return true;
  }
  return false;
}

bool Tile::canStepE(){
  if (this->empty && this->baseSymbol == '.') {
    return true;
  }
  return false;
}

bool Tile::isOwned(){return this->owned;}

bool Tile::isEmpty(){return this->empty;}

char Tile::getCurChar(){return this->currentSymbol;}

int Tile::getRow(){return this->row;}

int Tile::getCol(){return this->col;}

int Tile::getChamberNum(){return this->chamberNum;}

Potion* Tile::getPotion(){return this->potion;}

Gold* Tile::getGold(){return this->gold;}

Enemy* Tile::getEnemy(){return this->enemy;}

Player* Tile::getPlayer(){return this->player;}

vector<Tile*>* Tile::getEmptyTiles(){return &(this->emptyTiles);};

vector<Tile*>* Tile::getObserverTiles(){return &(this->observerTiles);};

void Tile::addChamberNum(int cn){
  if (!(this->owned)) {
    this->chamberNum = cn;
    this->owned = true;
    this->chamberRippleEffect(cn);
  }
}

void Tile::chamberRippleEffect(int cn){
  for (auto &i: this->observerTiles) {
    i->addChamberNum(cn);
  }
}
