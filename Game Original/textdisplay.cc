#include <iostream>
#include <vector>
#include <string>
#include "textdisplay.h"
#include "tile.h"

using namespace std;

TextDisplay::TextDisplay(vector<string>* gameMap, int rowSize, int colSize){
  int row = 0;
  while(row < rowSize){
    string currentLine = (*gameMap).at(row);
    int length = currentLine.length();
    vector<char> currentRow;
    char c;
    for (int i = 0; i < length; ++i){
      c = currentLine[i];
      currentRow.emplace_back(c);
    }
    this->display.emplace_back(currentRow);
    ++row;
  }
}

TextDisplay::~TextDisplay(){}

void TextDisplay::notify(Tile* t){
  int row = t->getRow();
  int col = t->getCol();
  int symbol = t->getCurChar();
  display[row][col] = symbol;
}

ostream &operator<<(ostream &out, const TextDisplay &td){
  for (auto &i: td.display) {
    for (auto &j: i) {
      out << j;
    }
    out << endl;
  }
  return out;
}
