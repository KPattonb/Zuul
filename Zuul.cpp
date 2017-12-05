#include "room.h"

struct Obj {
  char obj_name[10];
  char obj_text[150];
  Room *obj_location;
};

vector <Obj> objs;
vector <Room*> rooms;

void createObj(char *name, char *text, Room *location) {
  Obj i;

  strcpy(i.obj_name, name);
  strcpy(i.obj_text, text);
  i.obj_location = location;

  objs.push_back(i);
}

int main() {
  int G;
  char input[150];

  bool N;
  bool S;
  bool E;
  bool W;

  Room* inventory = new Room(0, "This is your inventory.");
  Room* box = new Room(1, "You are inside a box.");
  Room* party = new Room(2, "You are at a party. Everyone is dancing.");
  Room* drinkbar = new Room(3, "You are at the drink bar.");
  Room* pool = new Room(4, "You are at the pool.");
  Room* stairway = new Room(5, "You are in the building's stairwell.");
  Room* randapt = new Room(6, "You are in a stranger's apartment.");
  Room* randbath = new Room(7, "You are in the bathroom of the stranger's apartment.");
  Room* friendapt = new Room(8, "You are in your friend's apartment.");
  Room* friendbath = new Room(9, "You are in the bathroom of your friend's apartment.");
  Room* kitchen = new Room(10, "You are in your friend's kitchen.");
  Room* lobby = new Room(11, "You are in the lobby of the apartment building.");
  Room* backroom = new Room(12, "You are in the back room of the lobby. It's dark in here.");
  Room* landlord = new Room(13, "You are in the land lord's room. They aren't in here.");
  Room* parkinglot = new Room(14, "You are in the parking lot. Maybe you should get rid of the drinks before driving in your car.");
  Room* ledge = new Room(15, "You are are getting lose to the edge of the building. Be careful.");
  Room* car = new Room(16, "You are in your car. Time to go home.");

  //create the player
  createObj("You", "player #1.", box);

  //create the different objects
  createObj("beverage1", ", This is a canned drink.", drinkbar);
  createObj("beverage2", ", This is a canned drink.", randbath);
  createObj("beverage3", ", This is a canned drink.", kitchen);
  createObj("beverage4", ", This is a canned drink.", landlord);
  createObj("beverage5", ", This is a canned drink.", stairway);

  //set exits

  //box
  box->setExit(1, party);
  //party
  party->setExit(1, stairway);
  party->setExit(2, ledge);
  party->setExit(3, box);
  party->setExit(4, drinkbar);
  //drinkbar
  drinkbar->setExit(2, party);
  drinkbar->setExit(4, pool);
  //pool
  pool->setExit(2, drinkbar);
  //stairway
  stairway->setExit(1, friendapt);
  stairway->setExit(2, lobby);
  stairway->setExit(3, party);
  stairway->setExit(4, randapt);
  //randapt
  randapt->setExit(2, stairway);
  randapt->setExit(4, randbath);
  //randbath
  randbath->setExit(2, randapt);
  //friendapt
  friendapt->setExit(1, kitchen);
  friendapt->setExit(3, stairway);
  friendapt->setExit(4, friendbath);
  //friendbath
  friendbath->setExit(2, friendapt);
  //kitchen
  kitchen->setExit(3, friendapt);
  //lobby
  lobby->setExit(1, backroom);
  lobby->setExit(2, parkinglot);
  lobby->setExit(4, stairway);
  //backroom
  backroom->setExit(1, landlord);
  backroom->setExit(3, lobby);
  //landlord
  landlord->setExit(3, backroom);
  //parkinglot
  parkinglot->setExit(2, car);
  parkinglot->setExit(4, lobby);
  //ledge
  ledge->setExit(4, party);

  cout << "Welcome to Zuul!" << endl;

  while (true) {
    G = 0;

    //location
    cout << (objs[0].obj_location)->text << endl;

    //winning condition here
    if ((strcmp((objs[0].obj_location)->text, "You are in your car. Time to go home.") == 0) && (objs[1].obj_location != inventory) && (objs[2].obj_location != inventory) && (objs[3].obj_location != inventory) && (objs[4].obj_location != inventory) && (objs[5].obj_location != inventory)) {
	cout << "You made it home successfully!" << endl;
	cout << "You win!" << endl;
	return 0;
    }

    //losing condition
    if ((strcmp((objs[0].obj_location)->text, "You are are getting lose to the edge of the building. Be careful.") == 0) && (objs[1].obj_location == inventory) && (objs[2].obj_location != inventory) && (objs[3].obj_location != inventory) && (objs[4].obj_location != inventory) && (objs[5].obj_location != inventory)) {
	cout << "Oh no you fell off the building!" << endl;
	cout << "You lose!" << endl;
	return 0;
    }

    //list items
    cout << "Things in this room:" << endl;
    for (int i = 0; i < 5; i++) {
      if (objs[i].obj_location == objs[0].obj_location) {
	cout << " -- " << objs[i].obj_name << "\n" << endl;
	G++;
      }
    }
    if (G == 0) {
      cout << "None." << endl;
    }

    //output exits
    cout << "Exits to this room:" << endl;
    if ((objs[0].obj_location)->getExit(1) != NULL) {
      cout << "North" << endl;
      N = true;
    }
    else {
      N = false;
    }
    if ((objs[0].obj_location)->getExit(2) != NULL) {
      cout << "East" << endl;
      E = true;
    }
    else {
      E = false;
    }
    if ((objs[0].obj_location)->getExit(3) != NULL) {
      cout << "South" << endl;
      S = true;
    }
    else {
      S = false;
    }
    if ((objs[0].obj_location)->getExit(4) != NULL) {
      cout << "West" << endl;
      W = true;
    }
    else {
      W = false;
    }

    //Accept command input
    cout << "Command Options: INVENTORY, GO, GET, DROP, QUIT" << endl;
    cin.getline(input, 99);
    for (int i = 0; i < strlen(input); i++) {
      input[i] = toupper(input[i]);
    }

    //INVENTORY
    if (strcmp(input, "INVENTORY") == 0) {
      cout << "Inventory items: " << endl;
      G = 0;
      for (int i = 0; i < 5; i++) {
	if (objs[i].obj_location == inventory) {
	  cout << " -- " << objs[i].obj_name << endl;
	  G++;
	}
      }
      if (G == 0) {
	cout << "None." << endl;
      }
    }
    
    //GO
    if (strcmp(input, "GO") == 0) {
      cout << "Which direction? north, south, east, or west?" << endl;
      cin.getline(input, 99);
      for (int i = 0; i < strlen(input); i++) {
	input[i] = toupper(input[i]);
      }
      if (strcmp(input, "NORTH") == 0 && N) {
	objs[0].obj_location = objs[0].obj_location->getExit(1);
      }
      else if (strcmp(input, "EAST") == 0 && E) {
	objs[0].obj_location = objs[0].obj_location->getExit(2);
      }
      else if (strcmp(input, "SOUTH") == 0 && S) {
	objs[0].obj_location = objs[0].obj_location->getExit(3);
      }
      else if (strcmp(input, "WEST") == 0 && W) {
	objs[0].obj_location = objs[0].obj_location->getExit(4);
      }
      else {
	cout << "Input is not a valid exit." << endl;
      }
    }

    //GET
    if (strcmp(input, "GET") == 0) {
      G = 0;
      cout << "What item?" << endl;
      cin.getline(input, 99);
      for (int i = 0; i < strlen(input); i++) {
	input[i] = tolower(input[i]);
      }
      for (int i = 0; i < 5; i++) {
	if (objs[i].obj_location == objs[0].obj_location) {
	  if (strcmp(input, objs[i].obj_name) == 0) {
	    G++;
	    objs[i].obj_location = inventory;
	  }
	}
      }
      if (G == 0) {
	cout << "Not a valid object." << endl;
      }
    }

    //DROP
    if (strcmp(input, "DROP") == 0) {
      cout << "What item?" << endl;
      cin.getline(input, 99);
      for (int i = 0; i < strlen(input); i++) {
	input[i] = tolower(input[i]);
      }
      for (int i = 0; i < 5; i++) {
	if (objs[i].obj_location == inventory) {
	  if (strcmp(input, objs[i].obj_name) == 0) {
	    objs[i].obj_location = objs[0].obj_location;
	  }
	}
      }
    }

    //QUIT
    if (strcmp(input, "QUIT") == 0) {
      cout << "Thank you for playing!" << endl;
      return 0;
    }
    
  }
  return 0;
}
