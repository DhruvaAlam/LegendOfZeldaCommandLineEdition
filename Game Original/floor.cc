#include "floor.h"
#include "tile.h"
#include "chamber.h"
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "textdisplay.h"
#include "player.h"
#include "potion.h"
#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "merchant.h"
#include "dragon.h"
#include "phoenix.h"
#include "troll.h"
#include "gold.h"
#include "stairs.h"
#include "orc.h"
#include "dwarf.h"
#include "human.h"
#include "elf.h"
#include <ctime>

using namespace std;

void Floor::reset() {
    for(auto &i: this->chambers) {
        i->clearChamber();
    }
    this->p->resetTemp();
}


void Floor::printMap(){
    //output map
    output << *td;

    string race;
    char playerRace = this->p->getRace();
    if (playerRace == 'h'){
        race = "Human";
    } else if (playerRace == 'e'){
        race = "Elf";
    } else if (playerRace == 'd'){
        race = "Dwarf";
    } else {
        race = "Orc";
    }

    output << "Race: " << race << " Gold: " << p->getGold();

    //print spaces
    for (int i = 0; i < 48; ++i){
        output << " ";
    }

    output << "Floor " << floorNum << " " << endl;
    output << "Hp: " << p->getHp()<< endl;
    output << "Atk: " << p->getAtk() << endl;
    output << "Def: " << p->getDef() << endl;
    output << "Action: ";

}

Floor::Floor(vector<string>* gameMap, char character, ostream &output):
floorNum{1}, output{output}{
    int row = 0;
    string line = "";
    int totalRows = (*gameMap).size();
    this->totalnumRows = totalRows;
    int totalCols = (*gameMap).at(0).length();
    this->totalnumCols = totalCols;
    //width, height so col,row
    this->td = new TextDisplay(gameMap, this->totalnumRows, this->totalnumCols);

    while(row < totalRows){
        string currentLine = (*gameMap).at(row);
        int length = currentLine.length();
        vector<Tile *> currentRow;
        char c;
        for (int i = 0; i < length; ++i){
            c = currentLine[i];
            Tile *ptr;
            if ((c == '|') || (c == '-') || (c == ' ') || (c == '+') || (c == '#')){
                ptr = new Tile(c, row, i);
            } else { //anything else is a floor tile
                ptr = new Tile('.', row, i);
            }
            ptr->attach(td); //attach text display
            currentRow.emplace_back(ptr);
        }
        this->grid.emplace_back(currentRow);
        ++row;
    }
    //assign observers
    //this->grid.at(row).at(column)

    for (int r = 0; r < totalRows; ++r){
        for (int c = 0; c < totalCols; ++c){
            //add below
            if (r != (totalRows - 1)){
                this->grid.at(r).at(c)->attach(this->grid.at(r + 1).at(c));
            }
            //add above
            if (r != 0){
                this->grid.at(r).at(c)->attach(this->grid.at(r - 1).at(c));
            }
            //add left
            if (c != 0){
                this->grid.at(r).at(c)->attach(this->grid.at(r).at(c - 1));
            }
            //add right
            if (c != (totalCols - 1)){
                this->grid.at(r).at(c)->attach(this->grid.at(r).at(c + 1));
            }
            //add nw
            if (r == 0 || c == 0){
            } else {
                this->grid.at(r).at(c)->attach(this->grid.at(r - 1).at(c - 1));
            }
            //add sw
            if ((r == (totalRows -1)) || (c == 0)){
            } else {
                this->grid.at(r).at(c)->attach(this->grid.at(r + 1).at(c - 1));
            }
            //add ne
            if ((r == 0) || (c == (totalCols -1))){
            } else {
                this->grid.at(r).at(c)->attach(this->grid.at(r -1).at(c + 1));
            }
            //add se
            if ((r == (totalRows -1)) || (c == (totalCols -1))){
            } else {
                this->grid.at(r).at(c)->attach(this->grid.at(r + 1).at(c + 1));
            }
        }
    }



    //assign chambers
    int chamberNumber = -1;
    for (int r = 0; r < totalRows; ++r){
        for (int c = 0; c < totalCols; ++c){
            if (this->grid.at(r).at(c)->isOwned()){
                //do nothing
            } else {
                ++chamberNumber;
                this->grid.at(r).at(c)->addChamberNum(chamberNumber);
            }

        }
    }

    //create chambers
    for (int i = 0 ; i <= chamberNumber; ++i){
        Chamber * newC = new Chamber(i);
        this->chambers.emplace_back(newC);
    }

    //addTiles to chamber
    for (int r = 0; r < totalRows; ++r){
        for (int c = 0; c < totalCols; ++c){
            if (this->grid.at(r).at(c)->getCurChar() == '.'){
                int tileC = this->grid.at(r).at(c)->getChamberNum();
                this->chambers.at(tileC)->addTile(this->grid.at(r).at(c));
            }
        }
    }

    Player *playa = nullptr;

    if (character == 'h'){
        playa = new Human(this->grid.at(0).at(0));
    } else if (character == 'o'){
        playa = new Orc(this->grid.at(0).at(0));
    } else if (character == 'd'){
        playa = new Dwarf(this->grid.at(0).at(0));
    } else {
        playa = new Elf(this->grid.at(0).at(0));
    }
    this->p = playa;
}





Floor::~Floor(){
    for (auto &i: this->grid) {
        for (auto &j: i) {
            delete j;
        }
    }
    for (auto &i: this->chambers) {
        delete i;
    }
    //delete each individual tile
    /*
    for (int r = 0; r < totalnumRows; ++r){
    for (int c = 0; c < totalnumCols; ++c){
    delete this->grid.at(r).at(c);
}
}
//delete chambers
int numChamers = this->chambers.size();
for (int i = 0; i < numChamers; ++i){
delete this->chambers.at(i);
}*/
//delete TextDisplay
delete this->td;

delete this->p;

}

int Floor::randNum(int low, int high){
    int range = high - low + 1;
    int num = rand()%range + low;
    return num;
}

void Floor::init(){
    int numChambers = this->chambers.size();
    //spawn player
    int pos = randNum(0,numChambers - 1);
    int pos2 = randNum(0,numChambers - 1);
    while (pos2 == pos){
        pos2 = randNum(0,numChambers - 1); //choose a different chamber
    }

    this->chambers.at(pos)->addPlayer(this->p);
    this->chambers.at(pos2)->addStairs();

    //spawn 10 potions
    for (int i = 0; i < 10; ++i){
        int position = randNum(0,numChambers - 1);
        while (chambers.at(position)->isFull()){
            position = randNum(0,numChambers - 1);
        }
        chambers.at(position)->addPotion();
    }

    //spawn 10 gold
    for (int i = 0; i < 10; ++i){
        int position = randNum(0,numChambers - 1);
        while (chambers.at(position)->isFull()){
            position = randNum(0,numChambers - 1);
        }
        chambers.at(position)->addGold();
    }

    //spawn 20 enemies
    for (int i = 0; i < 20; ++i){
        int position = randNum(0,numChambers - 1);
        while (chambers.at(position)->isFull()){
            position = randNum(0,numChambers - 1);
        }
        chambers.at(position)->addEnemy();

    }
    this->printMap();
    if (this->floorNum == 1){
        this->output << "Player character has spawned." << endl;
    } else {
        this->output << "Player has moved onto the next floor." << endl;
    }
}

void Floor::init(vector<string>* gameMap){
    int row = 0;
    string line = "";
    while(row < this->totalnumRows){
        string currentLine = (*gameMap).at(row);
        int length = currentLine.length();

        char c;

        for (int i = 0; i < length; ++i){
            c = currentLine[i];
            Tile *tile = this->grid.at(row).at(i);
            int chamber = tile->getChamberNum();
            if (c == '@'){ //put character here
                tile->add(this->p);
            } else if (c =='0'){ // Restore health
                Potion *p = new Potion(tile, 0);
                tile->add(p);

            } else if (c =='1'){ // Boost Attack
                Potion *p = new Potion(tile, 1);
                tile->add(p);

            } else if (c =='2'){ //Boost Defence
                Potion *p = new Potion(tile, 2);
                tile->add(p);

            } else if (c =='3'){ //Poison Health
                Potion *p = new Potion(tile, 3);
                tile->add(p);

            } else if (c =='4'){ //wound attak
                Potion *p = new Potion(tile, 4);
                tile->add(p);

            } else if (c =='5'){ //wound defence
                Potion *p = new Potion(tile, 5);
                tile->add(p);

            } else if (c =='6'){ //normal gold
                Gold *g = new Gold(tile, 6);
                tile->add(g);

            } else if (c =='7'){ //small horde
                Gold *g = new Gold(tile, 7);
                tile->add(g);

            } else if (c =='8'){ //merchant horde
                Gold *g = new Gold(tile, 8);
                tile->add(g);

            } else if (c =='9'){ //dragon horde
                Gold *g = new Gold(tile, 9);
                tile->add(g);

            } else if (c == 'V'){ //vampire
                Enemy *e = new Vampire(tile);
                tile->add(e);
                this->chambers.at(chamber)->addEnemy(e);

            } else if (c == 'W'){ //werewolf
                Enemy *e = new WereWolf(tile);
                tile->add(e);
                this->chambers.at(chamber)->addEnemy(e);

            } else if (c == 'N'){ //goblin
                Enemy *e = new Goblin(tile);
                tile->add(e);
                this->chambers.at(chamber)->addEnemy(e);

            } else if (c == 'M'){ //merchant
                Enemy *e = new Merchant(tile);
                tile->add(e);
                this->chambers.at(chamber)->addEnemy(e);

            } else if (c == 'D'){ //dragon
                Enemy *e = new Dragon(tile);
                tile->add(e);
                this->chambers.at(chamber)->addEnemy(e);

            } else if (c == 'X'){  //phoenix
                Enemy *e = new Phoenix(tile);
                tile->add(e);
                this->chambers.at(chamber)->addEnemy(e);

            } else if (c == 'T'){  //troll
                Enemy *e = new Troll(tile);
                tile->add(e);
                this->chambers.at(chamber)->addEnemy(e);
            } else if (c == 92){ //stairs
                Stairs *s = new Stairs(tile);
                tile->add(s);
            }
        }
        ++row;
    }
    this->printMap();
    if (this->floorNum == 1){
        this->output << "Player character has spawned." << endl;
    } else {
        this->output << "Player has moved onto the next floor." << endl;
    }
}



int Floor::turn(string one, string two){
    int outcome = 0;
    bool invalid = false;
    int hpBefore = this->p->getHp();
    double goldBefore = this->p->getGold();
    string potionName = "";
    int damageDealt = 0;

    if ((two == "no") || (two == "so") || (two == "ea") || (two == "we") ||
    (two == "ne") || (two == "nw") || (two == "se") || (two == "sw")){
        if (one == "u"){ //direction
            outcome = this->floorPotion(two, &potionName);
        } else if (one == "a"){ //attack
            outcome = this->attackEnemy(two, &damageDealt);
        } else if (one == "move") { //move the player yo
            outcome = this->movePlayer(two);
            //check if player is on stair  and make bool won true
            if (outcome  == 2){
                ++this->floorNum;
                return 0;
            }
        } else { //invalid input
            invalid = true;
        }
    } else { //invalid input
        invalid = true;
    }
    this->moveEnemies();
    int hpAfter = this->p->getHp();
    double goldAfter = this->p->getGold();

    int hpChange = hpAfter - hpBefore;
    double goldChange = goldAfter - goldBefore;


    this->printMap();


    if (invalid){
        this->output << "Invalid input. Please refer to game manual to issue valid commands.";
    } else if (outcome  == 0){
        if (one == "u"){
            this->output << "No potion exisits in the specified direction.";
        } else if (one == "a"){
            this->output << "Cannot attack in the speicifed direction.";
        } else {
            this->output << "Cannot move in the specified direction.";
        }

    } else { //succesful move
        if (one == "a"){
            this->output << "Dealt " << damageDealt << " point(s) of damage to enemy.";
        } else if (one == "u") {
            this->output << "Player used a " << potionName << " potion.";
        } else {
            this->output << "Player succesfully moved.";
        }
    }
    //print out health change
    this->output << " HP change: " << hpChange << ". Gold change: " << goldChange << "." << endl;
    if (this->p->getHp() <= 0){
        return 1;
    }
    return 2;
}

int Floor::floorPotion(string dir, string *potionName){
    int playerRow = this->p->getTile()->getRow();
    int playerCol = this->p->getTile()->getCol();

    int row = playerRow;
    int col = playerCol;

    if (dir == "no"){
        row = playerRow - 1;
    } else if (dir == "so"){
        row = playerRow + 1;
    } else if (dir == "ea") {
        col = playerCol + 1;
    } else if (dir == "we") {
        col = playerCol - 1;
    } else if (dir == "ne") {
        row = playerRow - 1;
        col = playerCol + 1;
    } else if (dir == "nw") {
        row = playerRow - 1;
        col = playerCol - 1;
    } else if (dir == "se") {
        row = playerRow + 1;
        col = playerCol + 1;
    } else { // (dir == sw))
        row = playerRow + 1;
        col = playerCol - 1;
    }
    Tile *tilez  = this->grid.at(row).at(col);
    Potion *potion = tilez->getPotion();
    if (potion == nullptr){
        return 0;
    } else {
        *potionName = potion->getType();
        this->p->usePotion(potion);
        return 1;
    }
}

int Floor::attackEnemy(string dir, int *damage){
    int playerRow = this->p->getTile()->getRow();
    int playerCol = this->p->getTile()->getCol();

    int row = playerRow;
    int col = playerCol;

    if (dir == "no"){
        row = playerRow - 1;
    } else if (dir == "so"){
        row = playerRow + 1;
    } else if (dir == "ea") {
        col = playerCol + 1;
    } else if (dir == "we") {
        col = playerCol - 1;
    } else if (dir == "ne") {
        row = playerRow - 1;
        col = playerCol + 1;
    } else if (dir == "nw") {
        row = playerRow - 1;
        col = playerCol - 1;
    } else if (dir == "se") {
        row = playerRow + 1;
        col = playerCol + 1;
    } else { // (dir == sw))
        row = playerRow + 1;
        col = playerCol - 1;
    }
    Tile *tilez  = this->grid.at(row).at(col);
    Enemy *enemy = tilez->getEnemy();
    if (enemy == nullptr){
        return 0;
    } else {
        int dmg = this->p->attack(*enemy);
        *damage = dmg;
        return 1;
    }
}

int Floor::movePlayer(string dir){
    int playerRow = this->p->getTile()->getRow();
    int playerCol = this->p->getTile()->getCol();
    //cerr << "seg1" << endl;

    int row = playerRow;
    int col = playerCol;

    if (dir == "no"){
        row = playerRow - 1;
    } else if (dir == "so"){
        row = playerRow + 1;
    } else if (dir == "ea") {
        col = playerCol + 1;
    } else if (dir == "we") {
        col = playerCol - 1;
    } else if (dir == "ne") {
        row = playerRow - 1;
        col = playerCol + 1;
    } else if (dir == "nw") {
        row = playerRow - 1;
        col = playerCol - 1;
    } else if (dir == "se") {
        row = playerRow + 1;
        col = playerCol + 1;
    } else { // (dir == sw))
        row = playerRow + 1;
        col = playerCol - 1;
    }
    Tile *tilez  = this->grid.at(row).at(col);
    if (tilez->canStepP()){
        if (tilez->getCurChar() == 92){ //is it a stair
            return 2;
        } else {
            this->p->getTile()->clearTile();
            tilez->add(this->p);
            return 1;
        }
    } else { //invalid place to move onto
        return 0;
    }
}

void Floor::moveEnemies(){
    for (auto &i: this->chambers){
        i->moveEnemies();
    }
}

double Floor::getPlayerFinalScore() {
  char playerRace = this->p->getRace();
  if (playerRace == 'h') {
    return 1.5*(this->p->getGold());
  } else {
    return this->p->getGold();
  }
}
