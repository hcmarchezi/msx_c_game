#include <stdio.h>
#include <stdlib.h>

#include "game_sprite_collision.h"

void create_sprite_collision(sprite_collision* collision, game_sprite* from, game_sprite* to[], unsigned int to_sprite_count) {
	collision->from = from;
	for (int index=0; index < to_sprite_count; index++) {
		collision->to_many[index] = to[index];
		collision->collision[index] = 0;
	}
	collision->to_many_count = to_sprite_count;
}

void sprite_collision_check(sprite_collision* collision) {
	// printf("check\n");
	// printf("from=(%i, %i)\n", collision->from->x, collision->from->y);
	for(unsigned int idx=0; idx < collision->to_many_count; idx++) {
		int horizontal_match = abs(collision->from->x - collision->to_many[idx]->x) < 16;
		int vertical_match   = abs(collision->from->y - collision->to_many[idx]->y) < 16;
		//printf("to=(%i, %i) match: hor=%i ver=%i idx=%i\n", collision->to_many[idx]->x, collision->to_many[idx]->y, horizontal_match, vertical_match, idx);
		if (horizontal_match && vertical_match) {
			collision->collision[idx] = 1;
		}
	}
}

void sprite_collision_clear(sprite_collision* collision) {
	for (int index=0; index < SPRITE_SIZE; index++) {
		collision->collision[index] = 0;
	}
}
