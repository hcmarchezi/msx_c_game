#ifndef SPRITE_SWARM_H
#define SPRITE_SWARM_H

#include "sprite_type.h"

typedef struct {
	sprite_type** array;
	unsigned char size;
} sprite_swarm;


sprite_swarm* create_enemy_ships(
	int cols, int rows, int xi, int yi, char initial_sprite_id);

void free_enemy_ships(sprite_swarm* swarm);

void enemy_ships_move(sprite_swarm* swarm, char dx, char dy);

unsigned char display_enemy_ships(
	sprite_swarm* swarm, 
	void (*put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int));

#endif
