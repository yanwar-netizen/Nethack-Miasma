#include "miasma.h"

int addMonsters(Floor* floor) {
	
	floor->monsters = malloc(sizeof(Monster*) * 6);
	floor->monsterNos = 0;

	for (int x = 0; x < floor->roomNos; x++) {

		if (rand() % 2 || rand()%2 ) {
			floor->monsters[floor->monsterNos] = selectMonster(floor->floor);
			floor->monsters[floor->monsterNos]->position = malloc(sizeof(Position));
			monsterPos(floor->monsters[floor->monsterNos], floor->rooms[x]);

			floor->monsterNos++;
		}
	}
	return 1;
}

Monster* selectMonster(int floor) {
	int monster = 1;

	switch (floor) {
	case 1:
	case 2:
		break;
	case 3:
	case 4:
		monster = rand() % 2 + 1;
		break;
	case 5:
	default:
		monster = rand() % 3 + 1;
		break;
	}

	switch (monster) {
	case 1:
		return createMonster("⌠", 5, 1, 0, 1, 1);  //vermin
	case 2:
		return createMonster("α", 8, 2, 0, 2, 1); //mouse
	case 3:
		return createMonster("G", 12, 4, 1, 2, 5); //goblin
	default:
		return createMonster("⌠", 5, 1, 0, 2, 1);  //slightly stronger vermin
	}
}

Monster* createMonster(char* avatar, int health,int attack, int movement, int speed, int color) {
	Monster* newMonster;
	newMonster = malloc(sizeof(Monster));
	
	newMonster->alive = 1;
	newMonster->avatar = avatar;
	newMonster->health = health;
	newMonster->attack = attack;
	newMonster->movement = movement;
	newMonster->speed = speed;
	newMonster->color = color;

	return newMonster;
}

int monsterPos(Monster* monster, Room* room) {
	monster->position->x = rand() % (room->width-2) + room->position.x + 1;
	monster->position->y = rand() % (room->height-2) + room->position.y + 1;
	if (strcmp(monster->avatar, "G") != 0) {
		attron(COLOR_PAIR(monster->color));
		mvprintw(monster->position->y, monster->position->x, "%s", monster->avatar);
		attroff(COLOR_PAIR(monster->color));
	}
	else {
		attron(COLOR_PAIR(monster->color));
		mvprintw(monster->position->y, monster->position->x, "%s", monster->avatar);
		attroff(COLOR_PAIR(monster->color));
	}
	return 1;
}

int moveMonsters(Floor* floor) {

	for (int x = 0; x < floor->monsterNos; x++) {
		if(floor->monsters[x]->alive == 0){
			continue;
		}
		int oldX = floor->monsters[x]->position->x;
		int oldY = floor->monsters[x]->position->y;
		mvadd_wch(oldY, oldX, &floor->tiles[oldY][oldX]);

		if (floor->monsters[x]->movement == 0) {
			mvadd_wch(oldY, oldX, &floor->tiles[oldY][oldX]);
			movementRandom(floor->monsters[x]->position);

			if ((mvinch(floor->monsters[x]->position->y, floor->monsters[x]->position->x) & A_CHARTEXT) == '.') {
				attron(COLOR_PAIR(floor->monsters[x]->color));
				mvprintw(floor->monsters[x]->position->y, floor->monsters[x]->position->x, "%s", floor->monsters[x]->avatar);
				attroff(COLOR_PAIR(floor->monsters[x]->color));
			}

			else {

				floor->monsters[x]->position->y = oldY;
				floor->monsters[x]->position->x = oldX;
				attron(COLOR_PAIR(floor->monsters[x]->color));
				mvprintw(oldY, oldX, "%s", floor->monsters[x]->avatar);
				attroff(COLOR_PAIR(floor->monsters[x]->color));
			}
		}

		else {
			int oldX = floor->monsters[x]->position->x;
			int oldY = floor->monsters[x]->position->y;
			mvadd_wch(oldY, oldX, &floor->tiles[oldY][oldX]);
			movementSeeking(floor->monsters[x]->position, floor->user->position);
			attron(COLOR_PAIR(floor->monsters[x]->color));
			mvprintw(floor->monsters[x]->position->y, floor->monsters[x]->position->x, "%s", floor->monsters[x]->avatar);
			attroff(COLOR_PAIR(floor->monsters[x]->color));
		}

	}
	return 1;
}

int movementRandom(Position* start) {
	switch (rand() % 4) {
	case 0:
		start->x--; //left
		break;
	case 1:
		start->x++; //right
		break;
	case 2:
		start->y--; //top
		break;
	case 3:
		start->y++; //bottom
		break;
	default:
		break;
	}
}

int movementSeeking(Position* start, Position* destination) {
	if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && ((mvinch(start->y, start->x - 1)& A_CHARTEXT) == '.')) { //left
		start->x--;
	}
	else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && ((mvinch(start->y, start->x + 1) & A_CHARTEXT) == '.')) { //right
		start->x++;
	}
	else if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && ((mvinch(start->y - 1, start->x) & A_CHARTEXT) == '.')) {  //top
		start->y--;
	}
	else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && ((mvinch(start->y + 1, start->x) & A_CHARTEXT) == '.')) {  //bottom
		start->y++;
	}
	else {
		return 1;
	}
}

int killMonster(Monster* monster){
	attron(COLOR_PAIR(monster->color));
	mvprintw(monster->position->y, monster->position->x, ".");
	attroff(COLOR_PAIR(monster->color));
        monster->alive = 0;
	beep();
	return 1;
}	
