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
		return createMonster("⌠", 5, 0, 1);  //vermin
	case 2:
		return createMonster("α", 8, 0, 2); //mouse
	case 3:
		return createMonster("G", 12, 1, 2);
	default:
		return createMonster("⌠", 5, 0, 2);
	}
}

Monster* createMonster(char* avatar, int health, int movement, int speed) {
	Monster* newMonster;
	newMonster = malloc(sizeof(Monster));

	newMonster->avatar = avatar;
	newMonster->health = health;
	newMonster->movement = movement;
	newMonster->speed = speed;

	return newMonster;
}

int monsterPos(Monster* monster, Room* room) {
	monster->position->x = rand() % (room->width-2) + room->position.x + 1;
	monster->position->y = rand() % (room->height-2) + room->position.y + 1;
	if (strcmp(monster->avatar, "G") != 0) {
		attron(COLOR_PAIR(1));
		mvprintw(monster->position->y, monster->position->x, "%s", monster->avatar);
		attroff(COLOR_PAIR(1));
	}
	else {
		attron(COLOR_PAIR(5));
		mvprintw(monster->position->y, monster->position->x, "%s", monster->avatar);
		attroff(COLOR_PAIR(5));
	}
}

int moveMonsters(Floor* floor) {

	for (int x = 0; x < floor->monsterNos; x++) {

		int oldX = floor->monsters[x]->position->x;
		int oldY = floor->monsters[x]->position->y;
		mvadd_wch(oldY, oldX, &floor->tiles[oldY][oldX]);

		if (floor->monsters[x]->movement == 0) {
			mvadd_wch(oldY, oldX, &floor->tiles[oldY][oldX]);
			movementRandom(floor->monsters[x]->position);

			if ((mvinch(floor->monsters[x]->position->y, floor->monsters[x]->position->x) & A_CHARTEXT) == '.') {
				attron(COLOR_PAIR(1));
				mvprintw(floor->monsters[x]->position->y, floor->monsters[x]->position->x, "%s", floor->monsters[x]->avatar);
				attroff(COLOR_PAIR(1));
			}

			else {

				floor->monsters[x]->position->y = oldY;
				floor->monsters[x]->position->x = oldX;
				attron(COLOR_PAIR(1));
				mvprintw(oldY, oldX, "%s", floor->monsters[x]->avatar);
				attroff(COLOR_PAIR(1));
			}
		}

		else {
			int oldX = floor->monsters[x]->position->x;
			int oldY = floor->monsters[x]->position->y;
			mvadd_wch(oldY, oldX, &floor->tiles[oldY][oldX]);
			movementSeeking(floor->monsters[x]->position, floor->user->position);
			attron(COLOR_PAIR(5));
			mvprintw(floor->monsters[x]->position->y, floor->monsters[x]->position->x, "%s", floor->monsters[x]->avatar);
			attroff(COLOR_PAIR(5));
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