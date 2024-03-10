#ifndef SPRITE_TYPE_H
#define SPRITE_TYPE_H

#include "common_sprite.h"

typedef struct {
    position pos;
    unsigned int sprite_id;
    unsigned int sprite_pattern;
    unsigned int color;
} sprite_type;

void init_sprite(sprite_type* sprite, unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern);

void display_sprite(sprite_type* sprite, void (*put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int));

sprite_type* create_sprite(unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern);

#endif
