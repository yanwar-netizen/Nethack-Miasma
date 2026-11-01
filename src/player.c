#include "miasma.h"

Player* PlayerSetup() {

	Player* NewPlayer;
	NewPlayer = malloc(sizeof(Player));
	NewPlayer->position = malloc(sizeof(Position));
	NewPlayer->position->y = 11;
	NewPlayer->position->x = 6;
	NewPlayer->Health = 20;
	NewPlayer->Mana = 10;

	mvprintw(NewPlayer->position->y, NewPlayer->position->x, "@");
	move(NewPlayer->position->y, NewPlayer->position->x);

	return NewPlayer;
}


Position *ControlInput(char input, Player* user) {
	
	Position  *newPosition;
	newPosition = malloc(sizeof(Position));

	newPosition->x = user->position->x;
	newPosition->y = user->position->y;

	switch (input) {
		case 'w':
			newPosition->y = user->position->y - 1;
			newPosition->x= user->position->x;
			break;
		case 'a':
			newPosition->y = user->position->y;
			newPosition->x = user->position->x - 1;
			break;
		case 's':
			newPosition->y= user->position->y + 1;
			newPosition->x = user->position->x;
			break;
		case 'd':
			newPosition->y = user->position->y;
			newPosition->x = user->position->x + 1;
			break;
		default:
			break;
	}

	return newPosition;
}

int CheckPosition(Position *newPosition, Player* user, cchar_t** floor) {

	switch (mvinch(newPosition->y, newPosition->x) & A_CHARTEXT) {
		case '|':
		case '#':
		case '.':
		case '-':
			MoveUser(newPosition, user, floor);
			break;
		default:
			break;
	}

	free(newPosition);

	return 0;
}

int MoveUser(Position* newPosition, Player* user, cchar_t** floor) {

	mvadd_wch(user->position->y, user->position->x, &floor[user->position->y][user->position->x]);

	user->position->x = newPosition->x;
	user->position->y = newPosition->y;

	mvprintw(user->position->y, user->position->x, "@");
	move(user->position->y, user->position->x);
}