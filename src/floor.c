#include "miasma.h"

Floor* createFloor(int floor) {

	Floor* newFloor = malloc(sizeof(Floor));

	newFloor->floor = floor;
	newFloor->roomNos = 4;
	newFloor->monsterNos = 2;
	newFloor->rooms = RoomSetup();
	newFloor->tiles = saveFloor();

	addMonsters(newFloor);

	return newFloor;
}
//control area for room & door setup
Room** RoomSetup() {
	Room** rooms;
	rooms = malloc(sizeof(Room*) * 8);
	// included only inner width and height

	rooms[0] = CreateRoom(10, 5, 5, 13);
	DrawRoom(rooms[0]);
	rooms[1] = CreateRoom(5, 20, 3, 10);
	DrawRoom(rooms[1]);
	rooms[2] = CreateRoom(13, 33, 4, 13);
	DrawRoom(rooms[2]);
	rooms[3] = CreateRoom(6, 42, 3, 4);
	DrawRoom(rooms[3]);

	ConnectDoors(&rooms[0]->doors[1], &rooms[1]->doors[3]);
	ConnectDoors(&rooms[0]->doors[0], &rooms[1]->doors[2]);
	ConnectDoors(&rooms[1]->doors[1], &rooms[2]->doors[0]);
	ConnectDoors(&rooms[1]->doors[0], &rooms[3]->doors[0]);

	return rooms;
}

//save tiles
cchar_t** saveFloor() {

	cchar_t** position;
	position = malloc(sizeof(cchar_t*) * 100);

	for (int y= 0; y < 100; y++) {
		position[y] = malloc(sizeof(cchar_t)*100);
		for (int x = 0; x < 100; x++) {
			mvin_wch(y, x, &position[y][x]);
		}
	}

	return position;
}