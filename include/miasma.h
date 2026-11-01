#ifndef H_MIASMA
#define H_MIASMA
#define _XOPEN_SOURCE_EXTENDED 1
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

typedef struct Floor {
	int floor;
	int roomNos;
	int monsterNos;
	cchar_t** tiles;

	struct Room** rooms;
	struct Monster** monsters;
	struct Player* user;

} Floor;

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
	
	Position* position;
	int Health;
	int Mana;

} Player;

typedef struct Monster {

	Position* position;
	int health;
	char* avatar; 
	int movement;

} Monster;

//main function
int Screen();

//For player setup
Player* PlayerSetup();
Position* ControlInput(char input, Player* user);
int CheckPosition(Position *newPosition, Player* user, cchar_t** floor);
int MoveUser(Position *newPosition, Player* user, cchar_t** floor);

//floor
Floor* createFloor(int floor);

//For room setup
Room** RoomSetup();
cchar_t** saveFloor();

//functions to implement the setup room
Room* CreateRoom(int x, int y, int height, int width);
int DrawRoom(Room* room);
int ConnectDoors(Position* DoorA, Position* DoorB);

//monsters 
int addMonsters(Floor* floor);
Monster* selectMonster(int floor);
Monster* createMonster(char* avatar, int health, int movement);
int monsterPos(Monster* monster, Room* room);

//monster movements
int moveMonsters(Floor* floor);
int movementSeeking(Position* start, Position* destination);
int movementRandom(Position* start);


#endif