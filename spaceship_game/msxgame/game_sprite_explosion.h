#ifndef GAME_SPRITE_EXPLOSION_H
#define GAME_SPRITE_EXPLOSION_H

#include "game_sprite.h"

typedef struct {
    game_sprite* sprite;
    unsigned int* pattern_ids;
    unsigned int* sound_tones;
    unsigned int idx;
    unsigned int size;
} game_sprite_explosion;

game_sprite_explosion* game_sprite_explosion_new(unsigned int size);

int game_sprite_explosion_has_next(game_sprite_explosion* explosion);

void game_sprite_explosion_next(game_sprite_explosion* explosion);

unsigned int game_sprite_explosion_pattern_id(game_sprite_explosion* explosion);

unsigned int game_sprite_explosion_sound_tone(game_sprite_explosion* explosion);

#endif