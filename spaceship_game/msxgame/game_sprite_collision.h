#ifndef GAME_SPRITE_COLLISION_H
#define GAME_SPRITE_COLLISION_H

#include "game_sprite.h"

#define SPRITE_SIZE 16

typedef struct {
	game_sprite* from;
	game_sprite* to_many[SPRITE_SIZE];
	unsigned int collision[SPRITE_SIZE];
	unsigned int to_many_count;
} sprite_collision;

void create_sprite_collision(sprite_collision* collision, game_sprite* from, game_sprite* to[], unsigned int to_sprite_count);

void sprite_collision_check(sprite_collision* collision);

void sprite_collision_clear(sprite_collision* collision);

#endif
