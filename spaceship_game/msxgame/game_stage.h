#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include "game_sprite.h"

typedef struct {

  game_sprite* enemies;
  unsigned int enemy_count;

  unsigned char* tiles;
  unsigned int tile_count;
  
  unsigned char* channel_0_music_notes;
  unsigned char* channel_1_music_notes;
  unsigned int music_note_count;

} game_stage;

game_stage* game_stage_new(unsigned int enemy_count, unsigned int tile_count, unsigned int music_note_count);

void game_stage_free(game_stage* stage);

#endif
