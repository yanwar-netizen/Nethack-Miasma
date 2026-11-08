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
		mvprintw(0, 0, "Press any of the WASD key to move.");
		mvprintw(1, 0, "Press q to quit at any time!");
		mvprintw(20, 0, "Those in red and green are monsters, they do not do anything... for now.");

		newPosition = ControlInput(ch, floor->user);
		CheckPosition(newPosition, floor);
		moveMonsters(floor);
		move(floor->user->position->y, floor->user->position->x);
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

	init_color(COLOR_YELLOW, 400, 250, 50);

	init_pair(1, COLOR_RED, COLOR_BLACK); //MONSTERS
	init_pair(2, COLOR_CYAN, COLOR_BLACK); //WALLS
	init_pair(3, COLOR_YELLOW, COLOR_BLACK); //GROUND
	init_pair(4, COLOR_WHITE, COLOR_BLACK); //PLAYER
	init_pair(5, COLOR_GREEN, COLOR_BLACK); //GOBLIN

	printw(" -----------------\n| Nethack-Miasma | \n -----------------");
	refresh();
	printw("\n\n ...Dark Miasma is seeping from the depths of the dungeon...");
	refresh();
	printw("\n\n\n Press any button to continue.");
	refresh();

	getch();
	
	return 0;
}
