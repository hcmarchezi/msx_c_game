#include "game_sprite_explosion.h"

#include <stdlib.h>

game_sprite_explosion* game_sprite_explosion_new(unsigned int size) {
  game_sprite_explosion* explosion = (game_sprite_explosion*)malloc(sizeof(game_sprite_explosion));
  explosion->idx = 0;
  explosion->size = size;
  explosion->pattern_ids = (unsigned int*)malloc(sizeof(unsigned int)*size);
  explosion->sound_tones = (unsigned int*)malloc(sizeof(unsigned int)*size);
  return explosion;
}

int game_sprite_explosion_has_next(game_sprite_explosion* explosion) {
  return (explosion->idx < explosion->size - 1);
}

void game_sprite_explosion_next(game_sprite_explosion* explosion) {
  explosion->idx++;
}

unsigned int game_sprite_explosion_pattern_id(game_sprite_explosion* explosion) {
  return explosion->pattern_ids[explosion->idx];
}

unsigned int game_sprite_explosion_sound_tone(game_sprite_explosion* explosion) {
  return explosion->sound_tones[explosion->idx];
}
