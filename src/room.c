#include "miasma.h"

Room* CreateRoom(int y, int x, int height, int width) {

	Room* NewRoom;
	NewRoom = malloc(sizeof(Room));
	NewRoom->position.x = x;
	NewRoom->position.y = y;
	NewRoom->height = height;
	NewRoom->width = width;
	NewRoom->doors = malloc(sizeof(Position) * 4);

	srand(time(NULL));
	NewRoom->doors[0].x = x + (rand() % width); //top
	NewRoom->doors[0].y = y;

	NewRoom->doors[1].x = x + width; //right
	NewRoom->doors[1].y = y + 1 + (rand() % height);

	NewRoom->doors[2].x = x - 1; //left
	NewRoom->doors[2].y = y + 1 + (rand() % height);

	NewRoom->doors[3].x = x + (rand() % width); //bottom
	NewRoom->doors[3].y = y + height + 1;

	return NewRoom;
}

int DrawRoom(Room* room) {
	int x, y;
	//I might want to change all these values in the future cro, it just works but looks just wrong ;-;
	for (x = room->position.x; x < room->position.x + room->width + 2; x++) {
		mvprintw(room->position.y, x - 1, "═");
		mvprintw(room->position.y + room->height + 1, x - 1, "═");
	}

	for (y = room->position.y; y < room->position.y + room->height; y++) {
		mvprintw(y + 1, room->position.x - 1, "░");
		mvprintw(y + 1, room->position.x + room->width, "░");
		for (x = room->position.x; x < room->position.x + room->width; x++) {

			mvprintw(y + 1, x, ".");
		}
	}

	for (int i = 0; i < 4; i++) {
		if (i == 0 || i == 3) {
			mvprintw(room->doors[i].y, room->doors[i].x, "-");
		}
		else {
			mvprintw(room->doors[i].y, room->doors[i].x, "|");
		}
	}
	refresh();
}

int ConnectDoors(Position* DoorA, Position* DoorB) {
	Position temp;
	Position prev;

	int count = 0;

	temp.x = DoorA->x;
	temp.y = DoorA->y;

	prev = temp;

	while (1) {
		if ((abs((temp.x - 1) - DoorB->x) < abs(temp.x - DoorB->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) { //left
			prev = temp;
			temp.x--;
		}
		else if ((abs((temp.x + 1) - DoorB->x) < abs(temp.x - DoorB->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) { //right
			prev = temp;
			temp.x++;
		}
		else if ((abs((temp.y - 1) - DoorB->y) < abs(temp.y - DoorB->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {  //top
			prev = temp;
			temp.y--;
		}
		else if ((abs((temp.y + 1) - DoorB->y) < abs(temp.y - DoorB->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {  //bottom
			prev = temp;
			temp.y++;
		}
		else {
			if (count == 0) {
				temp = prev;
				count++;
				continue;
			}
			else {
				return 0;
			}
		}
		mvprintw(temp.y, temp.x, "#");
	}
}

