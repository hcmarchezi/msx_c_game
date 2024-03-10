#ifndef MSX_STUB_H
#define MSX_STUB_H

#include<stdio.h>

void *put_sprite(unsigned char sprite_id, int x, int y, unsigned char color, unsigned char sprite_pattern) {
	printf("display: put_sprite%i, (%i, %i), %i, %i\n", sprite_id, x, y, color, sprite_pattern);
}

#endif