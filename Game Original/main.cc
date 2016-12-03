#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "floor.h"

using namespace std;

#define FLOORNUM 5
#define DEFAULTFLOORMAP "defaultfloor.txt"

bool startGameDefault(ostream &o, istream &i, Floor &cc3kGame) { //true if game restarts, false if game quits
  int floorNum = 1;
  int playerStatus = 2;
  srand(time(NULL));
  //0 if player has proceed to next floor
  //1 if player dies
  //2 else
  while (floorNum <= FLOORNUM) {
    playerStatus = 2;
    cc3kGame.reset();
    cc3kGame.init();
    while (playerStatus == 2) {
      string userIntput;
      string cmd1, cmd2 = "move";
      getline(i, userIntput);
      if (i.eof() || i.fail()) {
        i.clear();
        i.ignore();
        return false;
      }
      istringstream ssUserInput {userIntput};
      ssUserInput >> cmd1 >> cmd2;
      if (cmd1 == "r") return true;
      if (cmd1 == "q") return false;
      if (cmd2 == "move") {
        string temp = cmd1;
        cmd1 = cmd2;
        cmd2 = temp;
      }
      playerStatus = cc3kGame.turn(cmd1, cmd2);
    }
    if (playerStatus == 0) {
      floorNum++;
    } else if (playerStatus == 1) {
      o << "Player has died" << endl;
      string inp;
      do {
        o << "Do you want to play again?(y/n): ";
        i >> inp;
      } while (!(inp == "y" || inp == "n"));
      if (inp == "n") {
        return false;
      } else {
        return true;
      }
    }
  }
  o << "You have beaten CREEPER CRAWLER 3k!" <<endl;
  double score = cc3kGame.getPlayerFinalScore();
  o << "Your final score was: " << score << endl;
  string inp;
  do {
    o << "Do you want to play again?(y/n): ";
    i >> inp;
  } while (!(inp == "y" || inp == "n"));
  if (inp == "n") {
    return false;
  } else {
    return true;
  }
}

bool getGameMap(vector<string>& gameMap, ifstream& file) {
  string input;
  gameMap.clear();
  bool first = true;
  while(getline(file, input)) {
    gameMap.emplace_back(input);
    if (input[1] == '-' && first) {
      first = false; //the border has been reached
    } else if (input[1] == '-' && !first) {
      return true;
    }
  }
  return false;
}

bool startGameCustom(ostream &o, istream &i, Floor &cc3kGame, char*argv[]) { //true if game restarts, false if game quits
  int floorNum = 1;
  int playerStatus = 2;
  //0 if player has proceed to next floor
  //1 if player dies
  //2 else
  ifstream file{argv[1]};
  vector<string> gameMap;
  while (getGameMap(gameMap, file)) {
    playerStatus = 2;
    cc3kGame.reset(); //clears the board
    cc3kGame.init(&gameMap); //initializes the game with the map
    while (playerStatus == 2) {
      string userIntput;
      string cmd1, cmd2 = "move";
      getline(i, userIntput);
      if (i.eof() || i.fail()) {
        i.clear();
        i.ignore();
        return false;
      }
      istringstream ssUserInput {userIntput};
      ssUserInput >> cmd1 >> cmd2;
      if (cmd1 == "r") return true;
      if (cmd1 == "q") return false;
      if (cmd2 == "move") {
        string temp = cmd1;
        cmd1 = cmd2;
        cmd2 = temp;
      }
      playerStatus = cc3kGame.turn(cmd1, cmd2);
    }
    if (playerStatus == 0) {
      floorNum++;
    } else if (playerStatus == 1) {
      o << "Player has died" << endl;
      string inp;
      do {
        o << "Do you want to play again?(y/n): ";
        i >> inp;
      } while (!(inp == "y" || inp == "n"));
      if (inp == "n") {
        return false;
      } else {
        return true;
      }
    }
  }
  o << "You have beaten CREEPER CRAWLER 3k!" <<endl;
  o << "Your final score was: " << cc3kGame.getPlayerFinalScore() << endl;
  string inp;
  do {
    o << "Do you want to play again?(y/n): ";
    i >> inp;
  } while (!(inp == "y" || inp == "n"));
  if (inp == "n") {
    return false;
  } else {
    return true;
  }
}

int main(int argc, char *argv[]) {
  ostream &o = cout;
  istream &i = cin;
  bool restart = true;
  while (restart) {
    string input;
    o << "Do you want to select a race? (y/n): ";
    cin >> input;
    o << endl;
    if (input == "q") break;
    //Gets player's choice of character
    string character;
    if (input == "y") {
      o << "Which character do you want to play as?" << endl;
      o << "(h)uman, (d)warf, (e)lf or (o)rc:"<< endl;
      cin >> character;
    } else {
      character = "h";
    }
    if (character == "q") break;
    if (argc == 1) { //if no layout is provided
      ifstream file(DEFAULTFLOORMAP);
      vector<string> gameMap;
      string input;

      //initialize game
      while(getline(file, input)) {
        gameMap.emplace_back(input);
      }
      Floor cc3kGame {&gameMap, character[0], o};
      i.clear();
      i.ignore();
      restart = startGameDefault(o, i, cc3kGame); //starts the game
    } else { //if layout is provided
      ifstream file(argv[1]);
      vector<string> gameMap;

      //initialize game
      string input;
      bool first = true;
      while(getline(file, input)) {
        gameMap.emplace_back(input);
        if (input[1] == '-' && first) {
          first = false; //the border has been reached
        } else if (input[1] == '-' && !first) {
          break;
        }
      }

      Floor cc3kGame {&gameMap, character[0], o};
      i.clear();
      i.ignore();
      restart = startGameCustom(o, i, cc3kGame, argv);
    }
  }
}
