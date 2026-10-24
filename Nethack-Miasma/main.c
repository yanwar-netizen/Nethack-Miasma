#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>

typedef struct Player {
	int xPosition;
	int yPosition;
	int Health;
	int Mana;
} Player;

int Screen();
int Map();
Player* PlayerSetup();


int main() {
	int ch;
	Screen();
	clear();
	Map();
	getch();
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

	printw("-----------------\n| Nethack-Miasma | \n-----------------");
	refresh();
	//printw("\n\n Dark Miasma is seeping through the depths of the dungeon...");
	//refresh();
	//printw("\n\n\n Press any button to continue");
	//refresh();

	getch();
	return 0;
}
int Map() {
	mvprintw(10, 5, " ------------- ");
	mvprintw(11, 5, "|.............|");
	mvprintw(12, 5, "|.............|");
	mvprintw(13, 5, "|.............|");
	mvprintw(14, 5, "|.............|");
	mvprintw(15, 5, "|.............|");
	mvprintw(16, 5, " ------------- ");

	mvprintw(5, 20, " ----------");
	mvprintw(6, 20, "|..........|");
	mvprintw(7, 20, "|..........|");
	mvprintw(8, 20, "|..........|");
	mvprintw(9, 20, " ----------");
	return 0;
}