#include "miasma.h"

Room** Map() {
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

chtype** saveFloor() {
	chtype** position;
	position = malloc(sizeof(chtype*) * 100);
	for (int y= 0; y < 100; y++) {
		position[y] = malloc(sizeof(chtype)*100);
		for (int x = 0; x < 100; x++) {
			position[y][x] = mvinch(y, x);
		}
	}
	return position;
}