#include <iostream>
#include <vector>
#include <map>
#include "string.h"

using namespace std;

class Room {
 public:
  Room(int, char *);

  int getRoom();
  char *getText();
  void setExit(int direction, Room *exit);
  Room *getExit(int exit);

  int room;
  char *text;
  map<int, Room *> exits;
};
