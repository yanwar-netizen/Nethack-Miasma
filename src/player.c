#include "miasma.h"

Player* PlayerSetup() {

	Player* NewPlayer;
	NewPlayer = malloc(sizeof(Player));
	NewPlayer->position = malloc(sizeof(Position));
	NewPlayer->position->y = 11;
	NewPlayer->position->x = 6;
	NewPlayer->health = 20;
	NewPlayer->mana = 10;
	NewPlayer->attack = 5;

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

int CheckPosition(Position *newPosition, Floor * floor) {

	for(int i = 0; i < floor->monsterNos; i++){
		if (floor->monsters[i]->alive==0){
			continue;
		}
		if (floor->monsters[i]->position->x == newPosition->x && floor->monsters[i]->position->y == newPosition->y){
			combat(floor->user, floor->monsters[i], 1);

			if(floor->monsters[i]->alive == 0){
				setcchar(&floor->tiles[newPosition->y][newPosition->x], L".", A_NORMAL, floor->monsters[i]->color, NULL);
				return 1;
			}
		}
	}
        
	switch (mvinch(newPosition->y, newPosition->x) & A_CHARTEXT) {
		case '|':
		case '#':
		case '.':
		case '-':
			MoveUser(newPosition, floor->user, floor->tiles);
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
	attron(COLOR_PAIR(4));
	mvprintw(user->position->y, user->position->x, "@");
	move(user->position->y, user->position->x);
	attroff(COLOR_PAIR(4));
}
