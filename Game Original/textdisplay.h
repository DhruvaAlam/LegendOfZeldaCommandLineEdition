#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"

class Tile;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> display;
public:
  TextDisplay(std::vector<std::string>* gameMap, int rowSize, int colSize);
  ~TextDisplay() override;
  void notify(Tile* t) override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
