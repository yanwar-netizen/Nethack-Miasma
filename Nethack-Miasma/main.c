#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>

typedef struct Room {
	int xPosition;
	int yPosition;
	int height;
	int width;
} Room;

typedef struct Player {
	int xPosition;
	int yPosition;
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
	NewPlayer->yPosition = 11;
	NewPlayer->xPosition = 6;
	NewPlayer->Health = 20;
	NewPlayer->Mana = 10;
	mvprintw(NewPlayer->yPosition, NewPlayer->xPosition, "@");
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
	/**mvprintw(10, 5, " ------------- ");
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
	DrawRoom(rooms[0]);
}

Room* CreateRoom(int x, int y, int height, int width) {
	Room* NewRoom;
	NewRoom->xPosition = x;
	NewRoom->yPosition = y;
	NewRoom->height = height;
	NewRoom->width = width;
	return NewRoom;
}

int DrawRoom(Room* room) {
	int x, y;
	for (x = room->xPosition; x < room->xPosition + room->width; x++) {
		mvprintw(room->yPosition, x, "-");
		refresh();
		mvprintw(room->yPosition + room->height, x, "-");
		refresh();
	}
	for (y = room->yPosition; y < room->yPosition + room->height; y++) {
		mvprintw(y, room->xPosition, "|");
		mvprintw(y + room->width, room->xPosition, "|");
		refresh();
		for (x = room->xPosition; x < room->xPosition + room->width; x++) {
			mvprintw(y, x, ".");
			refresh();
		}
	}
}
int MoveUser(int y, int x, Player* user) {
	mvprintw(user->yPosition, user->xPosition, ".");
	user->yPosition = y;
	user->xPosition = x;
	mvprintw(user->yPosition, user->xPosition, "@");
	refresh();
	move(user->yPosition, user->xPosition);
	return 0;
}
int ControlInput(char input, Player* user) {
	int NewX, NewY;
	switch (input) {
	case 'w':
		NewY = user->yPosition - 1;
		NewX = user->xPosition;
		break;
	case 'a':
		NewY = user->yPosition;
		NewX = user->xPosition-1;
		break;
	case 's':
		NewY = user->yPosition+1;
		NewX = user->xPosition;
		break;
	case 'd':
		NewY = user->yPosition;
		NewX = user->xPosition+1;
		break;
	default:
		return 0;
	}
	CheckPosition(NewY, NewX, user);
}

int CheckPosition(int NewY, int NewX, Player* user) {
	switch (mvinch(NewY, NewX)) {
	case '.':
		MoveUser(NewY, NewX, user);
		break;
	default:
		MoveUser(user->yPosition, user->xPosition, user);
	}
	return 0;
}