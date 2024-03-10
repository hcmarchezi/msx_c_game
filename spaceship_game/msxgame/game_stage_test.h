#include "minunit/minunit.h"
#include "game_stage.h"


MU_TEST(test_game_stage_new) {
  unsigned int enemy_count = 3
  unsigned int tiles_count = 4
  unsigned int music_note_count = 5
  game_stage* stage = game_stage_new(enemy_count, tiles_count, music_note_count);
  
  stage->enemies[0] = game_sprite_new(0,   0, 200, 1, 2, 1);
  stage->enemies[1] = game_sprite_new(1, 100, 100, 2, 2, 1);
  stage->enemies[2] = game_sprite_new(2, 200,   0, 3, 2, 1);

  u_char tiles = { 0x10, 0x20, 0x30, 0x40 };
  for (unsigned int idx=0; idx < 4; idx++) {
    stage->tiles[idx] = tiles[idx];
  }

  u_char* channel_0_music_notes = "ABCDE";
  u_char* channel_1_music_notes = "FGABC";

  mu_check(stage->enemy_count == 3);
  mu_check(stage->enemies[0]->sprite_id == 0);
  mu_check(stage->enemies[0]->sprite_id == 1);
  mu_check(stage->enemies[0]->sprite_id == 2);

  mu_check(stage->tiles_count == 4);
  mu_check(stage->tiles[0] == 0x10);
  mu_check(stage->tiles[0] == 0x20);
  mu_check(stage->tiles[0] == 0x30);
  mu_check(stage->tiles[0] == 0x40);
  
  mu_check(stage->music_note_count == 5);
  mu_check(stage->channel_0_music_notes[0] == 'A');
  mu_check(stage->channel_0_music_notes[1] == 'B');
  mu_check(stage->channel_0_music_notes[2] == 'C');
  mu_check(stage->channel_0_music_notes[3] == 'D');
  mu_check(stage->channel_0_music_notes[4] == 'E');

  mu_check(stage->channel_1_music_notes[0] == 'F');
  mu_check(stage->channel_1_music_notes[1] == 'G');
  mu_check(stage->channel_1_music_notes[2] == 'A');
  mu_check(stage->channel_1_music_notes[3] == 'B');
  mu_check(stage->channel_1_music_notes[4] == 'C');
}

