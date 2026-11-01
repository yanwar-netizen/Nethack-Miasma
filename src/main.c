#include "miasma.h"

int main() {

	int ch;
	Position* newPosition;

	Floor* floor;

	// go to main screen
	Screen();
	clear();

	floor = createFloor(5);

	// intialise the user settings
	floor->user = PlayerSetup();

	while ((ch = tolower(getch())) != 'q') {
		newPosition = ControlInput(ch, floor->user);
		CheckPosition(newPosition, floor->user, floor->tiles);
		moveMonsters(floor);
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