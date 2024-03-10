#include "minunit/minunit.h"
#include "sprite_type.h"

#include<stdlib.h>

MU_TEST(test_create_sprite) {
  int x = 100;
  int y = 50;
  unsigned int sprite_id = 10;
  unsigned int sprite_pattern = 1;
  unsigned int color = 13;

  sprite_type* sprite = create_sprite(sprite_id, x, y, color, sprite_pattern);

  mu_check(sprite->pos.x == 100);
  mu_check(sprite->pos.y == 50);
  mu_check(sprite->sprite_id == 10);
  mu_check(sprite->sprite_pattern == 1);
  mu_check(sprite->color == 13);
}


MU_TEST(test_init_sprite) {
  int x = 100;
  int y = 50;
  unsigned int sprite_id = 10;
  unsigned int sprite_pattern = 1;
  unsigned int color = 13;

  sprite_type sprite;
  init_sprite(&sprite, sprite_id, x, y, color, sprite_pattern);

  mu_check(sprite.pos.x == 100);
  mu_check(sprite.pos.y == 50);
  mu_check(sprite.sprite_id == 10);
  mu_check(sprite.sprite_pattern == 1);
  mu_check(sprite.color == 13);
}

void msx_put_sprite_16(unsigned int id, int x, int y, unsigned int color, unsigned int pattern) {
  mu_check(id == 10);
  mu_check(x == 100);
  mu_check(y == 50);
  mu_check(color == 13);
  mu_check(pattern == 1);
}

MU_TEST(test_display_sprite) {
  sprite_type sprite;
  init_sprite(&sprite, 10, 100, 50, 13, 1);
  display_sprite(&sprite, &msx_put_sprite_16);
}


MU_TEST_SUITE(sprite_test_suite) {
  MU_RUN_TEST(test_init_sprite);
  MU_RUN_TEST(test_display_sprite);
}
