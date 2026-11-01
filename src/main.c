#include "miasma.h"

int main() {

	Player* user;
	int ch;
	Position* newPosition;

	Floor* floor;

	// go to main screen
	Screen();
	clear();

	floor = createFloor(3);

	// intialise the user settings
	user = PlayerSetup();

	while ((ch = getch()) != 'q') {
		newPosition = ControlInput(ch, user);
		CheckPosition(newPosition, user, floor->tiles);
	}

	//end game
	endwin();

	return 0;

}

int Screen() {

	setlocale(LC_ALL, "");

	initscr();
	noecho();
	cbreak();
	start_color();

	printw(" -----------------\n| Nethack-Miasma | \n -----------------");
	refresh();
	printw("\n\n ...Dark Miasma is seeping from the depths of the dungeon...");
	refresh();
	printw("\n\n\n Press any button to continue.");
	refresh();

	getch();
	
	return 0;
}