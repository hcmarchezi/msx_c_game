#include <stdio.h>
#include <stdlib.h>

#include "game_sprite_collision.h"

int detect_sprite_collision(game_sprite* sp1, game_sprite* sp2) {
	int x_diff = abs(sp1->x - sp2->x);
  	int y_diff = abs(sp1->y - sp2->y);
  	if ((x_diff < SPRITE_SIZE) && (y_diff < SPRITE_SIZE)) {
    	return 1;
  	}
  	return 0;
}