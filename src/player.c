#include "miasma.h"

Player* PlayerSetup() {
	Player* NewPlayer;
	NewPlayer = malloc(sizeof(Player));
	NewPlayer->position.y = 11;
	NewPlayer->position.x = 6;
	NewPlayer->Health = 20;
	NewPlayer->Mana = 10;
	mvprintw(NewPlayer->position.y, NewPlayer->position.x, "@");
	move(NewPlayer->position.y, NewPlayer->position.x);
	return NewPlayer;
}


Position *ControlInput(char input, Player* user) {
	Position  *newPosition;
	newPosition = malloc(sizeof(Position));

	newPosition->x = user->position.x;
	newPosition->y = user->position.y;

	switch (input) {
		case 'w':
			newPosition->y = user->position.y - 1;
			newPosition->x= user->position.x;
			break;
		case 'a':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x - 1;
			break;
		case 's':
			newPosition->y= user->position.y + 1;
			newPosition->x = user->position.x;
			break;
		case 'd':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x + 1;
			break;
		/*case 'h':
			HelpScreen();*/
		default:
			break;
	}

	return newPosition;
}

int CheckPosition(Position *newPosition, Player* user, chtype** floor) {

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

int MoveUser(Position* newPosition, Player* user, chtype** floor) {
	char buffer[8];

	sprintf(buffer, "%c", floor[user->position.y][user->position.x]);

	mvprintw(user->position.y, user->position.x, "%s",buffer);

	user->position.x = newPosition->x;
	user->position.y = newPosition->y;

	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);
}