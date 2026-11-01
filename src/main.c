#include "miasma.h"

int main() {

	int ch;
	Player *user;
	Position* newPosition;

	chtype** floor;
	setlocale(LC_ALL, "");

	// go to main screen
	Screen();
	clear();

	// go to the map
	Map();
	floor = saveFloor();

	mvaddch(0, 0, floor[7][42]);
	// intialise the user settings
	user = PlayerSetup();

	while ((ch = getch()) != 'q') {
		newPosition = ControlInput(ch, user);
		CheckPosition(newPosition, user, floor);
	}

	//end game
	endwin();

	return 0;

}

int Screen() {

	initscr();
	/*if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal doesn't support colors!");
		exit(1);
	}*/
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

/*int HelpScreen() {
	clear();
	printw("Movement buttons: \nW for Up, S for down, A for left, D for left.");
	printw("Exit button: Press q to exit.");
	getch();
	return 1;
}*/