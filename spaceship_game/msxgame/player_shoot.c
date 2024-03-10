#include "player_shoot.h"

#include<stdlib.h>

player_shoot* create_player_shoot(sprite_type* sprite, int dy) {
	player_shoot* shoot = (player_shoot*)malloc(sizeof(player_shoot));
	shoot->sprite = sprite;
	shoot->dy = dy;
	return shoot;
}

void free_player_shoot(player_shoot* shoot) {
	free(shoot->sprite);
	free(shoot);
}

void player_shoot_update_position(player_shoot* shoot) {
	if (shoot->sprite->pos.y < 200) {
		shoot->sprite->pos.y += shoot->dy;
	}
}

void player_shoot_set_position(player_shoot* shoot, position pos) {
	shoot->sprite->pos.x = pos.x;
	shoot->sprite->pos.y = pos.y;
}

unsigned char display_player_shoot(
		player_shoot* shoot, 
		void (*put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int)) {

	put_sprite_16(
		shoot->sprite->sprite_id,
		shoot->sprite->pos.x,
		shoot->sprite->pos.y,
		shoot->sprite->color,
		shoot->sprite->sprite_pattern);

	return 0;
}