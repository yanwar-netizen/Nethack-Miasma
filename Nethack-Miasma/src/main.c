#include "miasma.h"

int main() {

	int ch;
	Player* user;
	setlocale(LC_ALL, "");

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

int Screen() {

	initscr();
	noecho();
	cbreak();

	printw(" -----------------\n| Nethack-Miasma | \n -----------------");
	refresh();
	printw("\n\n ...Dark Miasma is seeping from the depths of the dungeon...");
	refresh();
	printw("\n\n\n Press any button to continue.");
	refresh();

	getch();
	
	return 0;
}

int HelpScreen() {
	clear();
	printw("Movement buttons: \nW for Up, S for down, A for left, D for left.");
	printw("Exit button: Press q to exit.");
	getch();
	return 1;
}