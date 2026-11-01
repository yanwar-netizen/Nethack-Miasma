#ifndef H_MIASMA
#define H_MIASMA
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

typedef struct Floor {
	int floor;
	int roomNos;
	int monsterNos;
	chtype** tiles;

	struct Room** room;
	struct Monster** monster;
}Floor;

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

typedef struct Monster {
	Position position;
	int Health;
} Monster;

//main function
int Screen();

//For player setup
Player* PlayerSetup();
Position* ControlInput(char input, Player* user);
int CheckPosition(Position *newPosition, Player* user, chtype **floor);
int MoveUser(Position *newPosition, Player* user, chtype **floor);

//floor
Floor* createFloor(int floor);

//For room setup
Room** RoomSetup();
chtype** saveFloor();

//functions to implement the setup room
Room* CreateRoom(int x, int y, int height, int width);
int DrawRoom(Room* room);
int ConnectDoors(Position* DoorA, Position* DoorB);

//extra
int DrawGrid(int x, int y);


#endif