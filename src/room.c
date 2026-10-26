#include "miasma.h"

Room** Map() {
	Room** rooms;
	rooms = malloc(sizeof(Room) * 5);
	// included only inner width and height
	/*mvprintw(10, 5, " ------------- ");
	mvprintw(11, 5, "|.............|");
	mvprintw(12, 5, "|.............|");
	mvprintw(13, 5, "|.............|");
	mvprintw(14, 5, "|.............|");
	mvprintw(15, 5, "|.............|");
	mvprintw(16, 5, " ------------- ");*/
	rooms[0] = CreateRoom(10, 5, 5, 13);
	DrawRoom(rooms[0]);

	/*mvprintw(5, 20, " ----------");
	mvprintw(6, 20, "|..........|");
	mvprintw(7, 20, "|..........|");
	mvprintw(8, 20, "|..........|");
	mvprintw(9, 20, " ----------");*/
	rooms[1] = CreateRoom(5, 20, 3, 10);
	DrawRoom(rooms[1]);
	rooms[2] = CreateRoom(13, 33, 4, 13);
	DrawRoom(rooms[2]);
	rooms[3] = CreateRoom(6, 42, 3, 4);
	DrawRoom(rooms[3]);

	ConnectDoors(&rooms[0]->doors[1], &rooms[1]->doors[3]);
	ConnectDoors(&rooms[0]->doors[0], &rooms[1]->doors[2]);
	ConnectDoors(&rooms[1]->doors[1], &rooms[2]->doors[0]);

}

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

	DrawGrid(75, 21);


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
	refresh();

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

	temp.x = DoorA->x;
	temp.y = DoorA->y;

	while (1) {
		if ((abs((temp.x - 1) - DoorB->x) < abs(temp.x - DoorB->x)) && (mvinch(DoorA->y, DoorB->x - 1) == ' ')) { //left
			mvprintw(temp.y, temp.x - 1, "#");
			temp.x--;
		}
		else if ((abs((temp.x + 1) - DoorB->x) < abs(temp.x - DoorB->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) { //right
			mvprintw(temp.y, temp.x + 1, "#");
			temp.x++;
		}
		else if ((abs((temp.y - 1) - DoorB->y) < abs(temp.y - DoorB->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {  //top
			mvprintw(temp.y - 1, temp.x, "#");
			temp.y--;
		}
		else if ((abs((temp.y + 1) - DoorB->y) < abs(temp.y - DoorB->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {  //bottom
			mvprintw(temp.y + 1, temp.x, "#");
			temp.y++;
		}
		else {
			return 0;
		}
	}
}

int DrawGrid(int x, int y) {
	for (int i = 0; i < y-3; i++) {
		mvprintw(i+2, 2, "|");
		mvprintw(i+2, x-2, "|");
	}
	for (int j = 3; j < x; j++) {
		mvprintw(2, j-1, "-");
		mvprintw(y-2, j-1, "-");
	}

	return 1;
}