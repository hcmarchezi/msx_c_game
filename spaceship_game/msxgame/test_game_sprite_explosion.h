#include "minunit/minunit.h"

#include "game_sprite_explosion.h"

MU_TEST(test_sprite_explosion_new) {
  unsigned int size = 5;
  game_sprite_explosion* explosion = game_sprite_explosion_new(size);
  unsigned int pattern_ids[] = {1, 2, 3, 4, 5};
  unsigned int sound_tones[] = {100, 200, 300, 400, 500};

  explosion->pattern_ids = &pattern_ids;
  explosion->sound_tones = &sound_tones;  

  mu_assert_int_eq(explosion->size, 5);
  for (unsigned int index = 0; index < 5; index++) {
    mu_check(explosion->pattern_ids[index] == pattern_ids[index]);
    mu_check(explosion->sound_tones[index] == sound_tones[index]);
  }

  free(explosion);
}

game_sprite_explosion* create_test_sprite_explosion() {
  game_sprite_explosion* explosion = game_sprite_explosion_new(3);
  unsigned int* pattern_ids = (unsigned int*)malloc(sizeof(unsigned int)*3);
  pattern_ids[0] = 1;
  pattern_ids[1] = 2;
  pattern_ids[2] = 3;
  unsigned int* sound_tones = (unsigned int*)malloc(sizeof(unsigned int)*3);
  sound_tones[0] = 100;
  sound_tones[1] = 200;
  sound_tones[2] = 300;
  explosion->pattern_ids = pattern_ids;
  explosion->sound_tones = sound_tones; 
  return explosion;
}

MU_TEST(test_game_sprite_explosion_next) {
  unsigned int pattern_id;
  unsigned int sound_tone;
  game_sprite_explosion* explosion = create_test_sprite_explosion();

  pattern_id = game_sprite_explosion_pattern_id(explosion);
  sound_tone = game_sprite_explosion_sound_tone(explosion);
  mu_check(pattern_id == 1);
  mu_check(sound_tone == 100);
  mu_check(game_sprite_explosion_has_next(explosion));
  
  game_sprite_explosion_next(explosion);
  pattern_id = game_sprite_explosion_pattern_id(explosion);
  sound_tone = game_sprite_explosion_sound_tone(explosion);
  mu_check(pattern_id == 2);
  mu_check(sound_tone == 200);
  mu_check(game_sprite_explosion_has_next(explosion));

  game_sprite_explosion_next(explosion);
  pattern_id = game_sprite_explosion_pattern_id(explosion);
  sound_tone = game_sprite_explosion_sound_tone(explosion);
  mu_check(pattern_id == 3);
  mu_check(sound_tone == 300);
  mu_check(game_sprite_explosion_has_next(explosion) != 1);
}

MU_TEST_SUITE(game_sprite_explosion_test_suite) {
  MU_RUN_TEST(test_sprite_explosion_new);
  MU_RUN_TEST(test_game_sprite_explosion_next);
}

