#include "game_sprite.h"

#include <stdlib.h>
#include <stdio.h>

void define_sprite_pattern(int sprite_pattern_id, const char* sprite_pattern, int (*vpoke)(int, int)) {
	int mem_idx = 0x3800 + sprite_pattern_id*32;
	for (int index=0; index < 32; index++) {		
		vpoke(mem_idx, sprite_pattern[index]);
		mem_idx++;
	}
}

void init_game_sprite(
		game_sprite* sprite,
		unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern, 
		int velocity, unsigned int* explosion_pattern, unsigned char explosion_count) {
	sprite->sprite_id = sprite_id;
	sprite->x = x;
	sprite->y = y;
	sprite->color = color;
	sprite->sprite_pattern = sprite_pattern;
	sprite->velocity = velocity;
	sprite->status = 'A';
	sprite->explosion_idx = 0;
	sprite->explosion_pattern = explosion_pattern;
	sprite->explosion_count = explosion_count;
}

void game_sprite_move(game_sprite* ship, unsigned int stick) {
	if (stick == 8 || stick == 1 || stick == 2) {
		ship->y -= ship->velocity;
	} else if (stick >= 4 && stick <= 6) {
		ship->y += ship->velocity;
	}

	if (stick >= 2 && stick <= 4) {
		ship->x += ship->velocity;
	} else if (stick >= 6 && stick <= 8) {
		ship->x -= ship->velocity;
	}
}

void game_sprite_get_position(game_sprite* ship, int* x, int* y) {
	*x = ship->x;
	*y = ship->y;
}

void game_sprite_display(
		game_sprite* ship, 
		void (*ptr_put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int)) {

	ptr_put_sprite_16(
		ship->sprite_id,
		ship->x,
		ship->y,
		ship->sprite_pattern,
		ship->color);

	if (ship->status == 'E') {
		if (ship->explosion_idx < ship->explosion_count) {
			ship->explosion_idx++;
			ship->sprite_pattern = ship->explosion_pattern[ship->explosion_idx];
		} else {
			ship->status = 'D';
			ship->x = 256;
			ship->y = 200;
			ship->sprite_pattern = ship->explosion_pattern[ship->explosion_count - 1];
		}
	}
}

void game_sprite_set_explosion_mode(game_sprite* ship) {
	ship->status = 'E';
	ship->sprite_pattern = ship->explosion_pattern[0];
	ship->color = 10;
}
