#include "game_sprite.h"

#include <stdlib.h>

void define_sprite_pattern(int sprite_pattern_id, const char* sprite_pattern, int (*vpoke)(int, int)) {
	int mem_idx = 0x3800 + sprite_pattern_id*32;
	for (int index=0; index < 32; index++) {		
		vpoke(mem_idx, sprite_pattern[index]);
		mem_idx++;
	}
}

void create_game_sprite(
		game_sprite* ship, 
		unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern, 
		int velocity) {
	ship->sprite_id = sprite_id;
	ship->x = x;
	ship->y = y;
	ship->color = color;
	ship->sprite_pattern = sprite_pattern;
	ship->velocity = velocity;
}

game_sprite* game_sprite_new(unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern, int velocity) {
	game_sprite* sprite = (game_sprite *)malloc(sizeof(game_sprite));
	create_game_sprite(sprite, sprite_id, x, y, color, sprite_pattern, velocity);
	return sprite;
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
}
