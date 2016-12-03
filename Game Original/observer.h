#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Tile;

class Observer {
public:
  virtual ~Observer() = default;
  virtual void notify(Tile* t) = 0; //t is Tile that called notify
};

#endif
