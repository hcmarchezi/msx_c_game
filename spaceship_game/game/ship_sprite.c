#include "ship_sprite.h"

#include <stdlib.h>

unsigned int SHIP_SPRITE_1 = 1;
unsigned int SHIP_SPRITE_2 = 3;
unsigned int SHIP_SPRITE_3 = 4;
unsigned int SHIP_SPRITE_4 = 5;

unsigned char explosion_patterns[] = {10, 11, 12, 13, 12, 11, 10};
unsigned char explosion_pattern_count = 7;

void create_ship_sprite_1(game_sprite* sprite, unsigned int sprite_id, int x, int y, unsigned int color) {
	int velocity = 1;	
	
	init_game_sprite(
		sprite, sprite_id, x, y, color, SHIP_SPRITE_1, 
		velocity, explosion_patterns, explosion_pattern_count);

	return sprite;
}

void create_ship_sprite_2(game_sprite* sprite, unsigned int sprite_id, int x, int y, unsigned int color) {
	int velocity = 1;	
	
	init_game_sprite(
		sprite, sprite_id, x, y, color, SHIP_SPRITE_2, 
		velocity, explosion_patterns, explosion_pattern_count);

	return sprite;
}

void create_ship_sprite_3(game_sprite* sprite, unsigned int sprite_id, int x, int y, unsigned int color) {
	int velocity = 1;	
	
	init_game_sprite(
		sprite, sprite_id, x, y, color, SHIP_SPRITE_3, 
		velocity, explosion_patterns, explosion_pattern_count);

	return sprite;
}

void create_ship_sprite_4(game_sprite* sprite, unsigned int sprite_id, int x, int y, unsigned int color) {
	int velocity = 1;	
	
	init_game_sprite(
		sprite, sprite_id, x, y, color, SHIP_SPRITE_4, 
		velocity, explosion_patterns, explosion_pattern_count);

	return sprite;
}
