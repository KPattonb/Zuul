#include "room.h"

Room::Room(int _room, char *_text) {
  room = _room;
  text = _text;
}

int Room::getRoom() {
  return room;
}

char *Room::getText() {
  return text;
}

void Room::setExit(int direction, Room *exit) {
  exits[direction] = exit;
}

Room *Room::getExit(int exit) {
  map<int, Room *>::iterator it;
  it = exits.find(exit);

  if (it != exits.end()) {
    return exits.find(exit)->second;
  }
  else {
    return NULL;
  }
}
