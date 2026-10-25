#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <time.h>

typedef struct Position {
	int x;
	int y;
} Position;
typedef struct Room {
	Position position;
	Position *doors;
	int height;
	int width;
} Room;

typedef struct Player {
	Position position;
	int Health;
	int Mana;
} Player;

int Screen();
Room** Map();
Player* PlayerSetup();
int ControlInput(char input, Player* user);
int CheckPosition(int NewY, int NewX, Player* user);
Room* CreateRoom(int x, int y, int height, int width);
int DrawRoom(Room* room);
int ConnectDoors(Position* DoorA, Position* DoorB);
int MoveUser(int y, int x, Player* user);

int main() {
	int ch;
	Player* user;
	// go to main screen
	Screen();
	clear();
	// go to the map
	Map();
	// intialise the user settings
	user = PlayerSetup();

	while ((ch = getch()) != 'q') {
		ch = tolower(ch);
		ControlInput(ch, user);
	}
	//end game
	endwin();

	return 0;

}
Player* PlayerSetup() {
	Player* NewPlayer;
	NewPlayer = malloc(sizeof(Player));
	NewPlayer->position.y = 11;
	NewPlayer->position.x = 6;
	NewPlayer->Health = 20;
	NewPlayer->Mana = 10;
	mvprintw(NewPlayer->position.y, NewPlayer->position.x, "@");
	return NewPlayer;
}

int Screen() {
	initscr();
	noecho();
	cbreak();

	printw("-----------------\n| Nethack-Miasma | \n-----------------");
	refresh();
	printw("\n\n ...Dark Miasma is seeping from the depths of the dungeon...");
	refresh();
	printw("\n\n\n Press any button to continue.");
	refresh();

	getch();
	return 0;
}
Room** Map(){
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

	ConnectDoors(&rooms[0]->doors[1], &rooms[1]->doors[3]);
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
	NewRoom->doors[2].y = y + 1 + (rand() %  height);

	NewRoom->doors[3].x = x + (rand() % width); //bottom
	NewRoom->doors[3].y = y + height + 1;


	return NewRoom;
}

int DrawRoom(Room* room) {
	int x, y;
	//I might want to change all these values in the future cro, it just works but looks just wrong ;-;
	for (x = room->position.x; x < room->position.x + room->width; x++) {
		mvprintw(room->position.y, x, "-");
		mvprintw(room->position.y + room->height + 1, x, "-");
	}
	for (y = room->position.y; y < room->position.y + room->height; y++) {
		mvprintw(y+1, room->position.x-1, "|");
		mvprintw(y+1, room->position.x+room->width, "|");
		refresh();
		for (x = room->position.x; x < room->position.x + room->width; x++) {
			mvprintw(y+1, x, ".");
			refresh();
		}
	}

	for (int i = 0; i < 4; i++) {
		mvprintw(room->doors[i].y, room->doors[i].x, "+");
	}
}

int ConnectDoors(Position* DoorA, Position* DoorB) {
	Position temp;

	temp.x = DoorA->x;
	temp.y = DoorA->y;

	while (1) {
		if ((abs((temp.x - 1) - DoorB->x) < abs(temp.x - DoorB->x)) && (mvinch(DoorA->y, DoorB->x-1) == ' ')) { //left
			mvprintw(temp.y , temp.x - 1, "#");
			temp.x--;
		}
		else if ((abs((temp.x +1 ) - DoorB->x) < abs(temp.x - DoorB->x)) && (mvinch(temp.y, temp.x+1) == ' ')) { //right
			mvprintw(temp.y, temp.x + 1, "#");
			temp.x++;
		}
		else if ((abs((temp.y - 1) - DoorB->y) < abs(temp.y - DoorB->y)) && (mvinch(temp.y-1 , temp.x) == ' ')) {  //top
			mvprintw(temp.y - 1, temp.x, "#");
			temp.y--;
		}
		else if ((abs((temp.y + 1) - DoorB->y) < abs(temp.y - DoorB->y)) && (mvinch(temp.y+1, temp.x) == ' ')) {  //bottom
			mvprintw(temp.y+1, temp.x, "#");
			temp.y++;
		}
		else {
			return 0;
		}
	}
}
int MoveUser(int y, int x, Player* user) {
	mvprintw(user->position.y, user->position.x, ".");
	user->position.y = y;
	user->position.x = x;
	mvprintw(user->position.y, user->position.x, "@");
	refresh();
	move(user->position.y, user->position.x);
	return 0;
}
int ControlInput(char input, Player* user) {
	int NewX, NewY;
	switch (input) {
	case 'w':
		NewY = user->position.y - 1;
		NewX = user->position.x;
		break;
	case 'a':
		NewY = user->position.y;
		NewX = user->position.x-1;
		break;
	case 's':
		NewY = user->position.y+1;
		NewX = user->position.x;
		break;
	case 'd':
		NewY = user->position.y;
		NewX = user->position.x+1;
		break;
	default:
		return 0;
	}
	CheckPosition(NewY, NewX, user);
}

int CheckPosition(int NewY, int NewX, Player* user) {
	switch (mvinch(NewY, NewX)) {
	case '+':
	case '#':
	case '.':
		MoveUser(NewY, NewX, user);
		break;
	default:
		MoveUser(user->position.y, user->position.x, user);
	}
	return 0;
}