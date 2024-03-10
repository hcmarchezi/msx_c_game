#include "sprite_type.h"

#include<stdlib.h>

void init_sprite(sprite_type* sprite, unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern) {    
    sprite->pos.x = x;
    sprite->pos.y = y;
    sprite->sprite_id = sprite_id;
    sprite->sprite_pattern = sprite_pattern;
    sprite->color = color;
}

void display_sprite(sprite_type* sprite, void (*put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int)) {
    put_sprite_16(sprite->sprite_id, sprite->pos.x, sprite->pos.y, sprite->color, sprite->sprite_pattern);
}

sprite_type* create_sprite(unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern) {
    sprite_type* sprite = (sprite_type*)malloc(sizeof(sprite_type));
    init_sprite(sprite, sprite_id, x, y, color, sprite_pattern);
    return sprite;
}
