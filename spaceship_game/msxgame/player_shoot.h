#ifndef PLAYER_SHOOT_H
#define PLAYER_SHOOT_H

#include "sprite_type.h"

typedef struct {
	sprite_type* sprite;
	int dy; // vertical velocity and orientation

} player_shoot;

player_shoot* create_player_shoot(sprite_type* sprite, int dy);

void free_player_shoot(player_shoot* shoot);

void player_shoot_update_position(player_shoot* shoot);

void player_shoot_set_position(player_shoot* shoot, position pos);

unsigned char display_player_shoot(
	player_shoot* shoot, 
	void (*put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int));

#endif