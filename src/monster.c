#include "miasma.h"

int addMonsters(Floor* floor) {
	
	floor->monsters = malloc(sizeof(Monster*) * 6);
	floor->monsterNos = 0;

	for (int x = 0; x < floor->roomNos; x++) {
		if (rand() % 2 || rand()%2 ) {
			floor->monsters[floor->monsterNos] = selectMonster(floor->floor);
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
		return createMonster("⌠", 5);  //vermin
	case 2:
		return createMonster("α", 8); //mouse
	case 3:
		return createMonster("G", 12);
	default:
		return createMonster("⌠", 5);
	}
}

Monster* createMonster(char* avatar, int health) {
	Monster* newMonster;
	newMonster = malloc(sizeof(Monster));

	newMonster->avatar = avatar;
	newMonster->health = health;

	return newMonster;
}

int monsterPos(Monster* monster, Room* room) {
	monster->position.x = rand() % (room->width-2) + room->position.x + 1;
	monster->position.y = rand() % (room->height-2) + room->position.y + 1;

	mvprintw(monster->position.y, monster->position.x, "%s", monster->avatar);
}

