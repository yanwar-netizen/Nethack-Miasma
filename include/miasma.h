#ifndef H_MIASMA
#define H_MIASMA
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

typedef struct Position {

	int x;
	int y;

} Position;

typedef struct Room {

	Position position;
	Position* doors;
	int height;
	int width;

} Room;

typedef struct Player {
	
	Position position;
	int Health;
	int Mana;

} Player;

int Screen();
int HelpScreen();

//For player setup
Player* PlayerSetup();
int ControlInput(char input, Player* user);
int CheckPosition(int NewY, int NewX, Player* user);
int MoveUser(int y, int x, Player* user);

//For room setup
Room** Map();
Room* CreateRoom(int x, int y, int height, int width);
int DrawRoom(Room* room);
int ConnectDoors(Position* DoorA, Position* DoorB);

int DrawGrid(int x, int y);


#endif