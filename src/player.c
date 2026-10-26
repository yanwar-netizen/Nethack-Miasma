#include "miasma.h"

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

int MoveUser(int y, int x, Player* user) {

	chtype mixedOldTile = mvinch(20, 34);
	char OldTile = mixedOldTile & A_CHARTEXT;
	mvaddch(20, 34, OldTile);
	mvprintw(20, 10, "Current Standing Tile: [ ] ");
	mvprintw(21, 10, "press h for help.");

	if (OldTile == ' ' || OldTile == '\0') {
		OldTile = '.';
	}

	mvaddch(user->position.y, user->position.x, OldTile);

	chtype mixedOldTile2 = mvinch(y, x);
	char OldTile2 = mixedOldTile2 & A_CHARTEXT;

	mvaddch(20, 34, OldTile2);

	switch (OldTile2) {
		case '.':
			mvprintw(21, 10, "                     ");
			refresh();
			mvprintw(21, 10, "This is a Floor Tile.");
		break;
		case '|':
		case '-':
			mvprintw(21, 10, "                     ");
			refresh();
			mvprintw(21, 10, "This is a Door.");
		break;
		case '#':
			mvprintw(21, 10, "                     ");
			refresh();
			mvprintw(21, 10, "This is a Path Tile.");
		break;
	}
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
			NewX = user->position.x - 1;
			break;
		case 's':
			NewY = user->position.y + 1;
			NewX = user->position.x;
			break;
		case 'd':
			NewY = user->position.y;
			NewX = user->position.x + 1;
			break;
		/*case 'h':
			HelpScreen();*/
		default:
			return 0;
	}

	CheckPosition(NewY, NewX, user);
}

int CheckPosition(int NewY, int NewX, Player* user) {

	switch (mvinch(NewY, NewX) & A_CHARTEXT) {
		case '|':
		case '#':
		case '.':
		case '-':
			MoveUser(NewY, NewX, user);
			break;
		default:
			MoveUser(user->position.y, user->position.x, user);
	}

	/*chtype mixedChar = mvinch(NewY, NewX);
	char cleanChar = mixedChar & A_CHARTEXT;
	if (cleanChar ==  '|' || cleanChar == '#' || cleanChar == '.' || cleanChar == '-') {
		MoveUser(NewY, NewX, user);
	}
	else {
		MoveUser(user->position.y, user->position.x, user);
	}*/
	return 0;
}