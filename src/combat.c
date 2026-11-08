#include "miasma.h"

int combat(Player * player, Monster * monster, int first){
	if (first == 1){
		monster->health -= player->attack;
		if ( monster-> health > 0){
			player->health -= monster->attack;
		}
		else {
			killMonster(monster);
		}
	}
	else {
		player->health -= monster->health;
		if ( player->health > 0){
			monster->health -= player->attack;
		}
	}
}
