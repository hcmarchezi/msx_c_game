#include "minunit/minunit.h"
#include "animated_sprite.h"

void test_animated_sprite_setup(void) { /* Nothing */ }

void test_animated_sprite_teardown(void) { /* Nothing */ }

animated_sprite_type* anim_sprite = 0;

MU_TEST(test_create_animated_sprite) {
  position pos; pos.x = 100; pos.y = 50;
  int step = 2;
  unsigned int sprite_id = 10;
  char horizontal_orientation = 'R';
  
  pattern_range move_right_patterns; 
  move_right_patterns.start = 1;
  move_right_patterns.end = 4;

  pattern_range move_left_patterns; 
  move_left_patterns.start = 5;
  move_left_patterns.end = 8;

  pattern_collection right_poses_patterns;
  right_poses_patterns.down = 9;
  right_poses_patterns.up   = 11;
  right_poses_patterns.ground_kick = 13;  
  right_poses_patterns.down_kick = 15;
  right_poses_patterns.up_kick = 17;

  pattern_collection left_poses_patterns;
  left_poses_patterns.down = 10;
  left_poses_patterns.up   = 12;
  left_poses_patterns.ground_kick = 14;
  left_poses_patterns.down_kick = 16;
  left_poses_patterns.up_kick = 18;

  anim_sprite = create_animated_sprite(
    pos, step, horizontal_orientation, sprite_id, 
    move_right_patterns, move_left_patterns,
    left_poses_patterns, right_poses_patterns);

  mu_check(anim_sprite->pos.x == 100);
  mu_check(anim_sprite->pos.y == 50);
  mu_check(anim_sprite->step == 2);
  mu_check(anim_sprite->horizontal_orientation == 'R');
  mu_check(anim_sprite->sprite_id == 10);
  mu_check(anim_sprite->pattern_idx == 0);
  mu_check(anim_sprite->jump_status == 'G');

  mu_check(anim_sprite->move_right_patterns.start == 1);
  mu_check(anim_sprite->move_right_patterns.end == 4);

  mu_check(anim_sprite->right_poses_patterns.down == 9);
  mu_check(anim_sprite->right_poses_patterns.up == 11);
  mu_check(anim_sprite->right_poses_patterns.ground_kick == 13);

  mu_check(anim_sprite->move_left_patterns.start == 5);
  mu_check(anim_sprite->move_left_patterns.end == 8);
  mu_check(anim_sprite->left_poses_patterns.down == 10);
  mu_check(anim_sprite->left_poses_patterns.up == 12);
  mu_check(anim_sprite->left_poses_patterns.ground_kick == 14);
}

MU_TEST(test_animated_sprite_move_right) {
  anim_sprite->pattern_idx = 0;
  anim_sprite->pos.x = 100;
  anim_sprite->horizontal_orientation = 'X';
  
  animated_sprite_move_right(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 1);
  mu_check(anim_sprite->pos.x == 102);
  mu_check(anim_sprite->horizontal_orientation == 'R');

  animated_sprite_move_right(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 2);
  mu_check(anim_sprite->pos.x == 104);
  mu_check(anim_sprite->horizontal_orientation == 'R');

  animated_sprite_move_right(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 3);
  mu_check(anim_sprite->pos.x == 106);
  mu_check(anim_sprite->horizontal_orientation == 'R');

  animated_sprite_move_right(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 4);
  mu_check(anim_sprite->pos.x == 108);
  mu_check(anim_sprite->horizontal_orientation == 'R');

  animated_sprite_move_right(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 1);
  mu_check(anim_sprite->pos.x == 110);
  mu_check(anim_sprite->horizontal_orientation == 'R');

  anim_sprite->pattern_idx = 20;
  anim_sprite->horizontal_orientation = 'X';
  animated_sprite_move_right(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 1);
  mu_check(anim_sprite->pos.x == 112);
  mu_check(anim_sprite->horizontal_orientation == 'R');
}

MU_TEST(test_animated_sprite_move_left) {
  anim_sprite->pattern_idx = 1;
  anim_sprite->horizontal_orientation = 'X';
  anim_sprite->pos.x = 110;
  
  animated_sprite_move_left(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 5);
  mu_check(anim_sprite->pos.x == 108);
  mu_check(anim_sprite->horizontal_orientation == 'L');

  animated_sprite_move_left(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 6);
  mu_check(anim_sprite->pos.x == 106);
  mu_check(anim_sprite->horizontal_orientation == 'L');

  animated_sprite_move_left(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 7);
  mu_check(anim_sprite->pos.x == 104);
  mu_check(anim_sprite->horizontal_orientation == 'L');

  animated_sprite_move_left(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 8);
  mu_check(anim_sprite->pos.x == 102);
  mu_check(anim_sprite->horizontal_orientation == 'L');

  animated_sprite_move_left(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 5);
  mu_check(anim_sprite->pos.x == 100);
  mu_check(anim_sprite->horizontal_orientation == 'L');

  anim_sprite->pattern_idx = 20;
  anim_sprite->horizontal_orientation = 'X';
  animated_sprite_move_left(anim_sprite);
  mu_check(anim_sprite->pattern_idx == 5);
  mu_check(anim_sprite->pos.x == 98);
  mu_check(anim_sprite->horizontal_orientation == 'L');
}

MU_TEST(test_animated_sprite_move_down) {
  anim_sprite->horizontal_orientation = 'R';
  anim_sprite->pos.x = 110;
  animated_sprite_move_down(anim_sprite);
  mu_check(anim_sprite->pos.x == 110);
  mu_check(anim_sprite->horizontal_orientation == 'R');
  mu_check(anim_sprite->pattern_idx == 9);

  anim_sprite->horizontal_orientation = 'L';
  anim_sprite->pos.x = 150;
  animated_sprite_move_down(anim_sprite);
  mu_check(anim_sprite->pos.x == 150);
  mu_check(anim_sprite->horizontal_orientation == 'L');
  mu_check(anim_sprite->pattern_idx == 10);
}

MU_TEST(test_animated_sprite_move_up) {
  anim_sprite->horizontal_orientation = 'R';
  anim_sprite->pos.x = 120;
  animated_sprite_move_up(anim_sprite);
  mu_check(anim_sprite->pos.x == 120);
  mu_check(anim_sprite->horizontal_orientation == 'R');
  mu_check(anim_sprite->pattern_idx == 1);

  anim_sprite->horizontal_orientation = 'L';
  anim_sprite->pos.x = 140;
  animated_sprite_move_up(anim_sprite);
  mu_check(anim_sprite->pos.x == 140);
  mu_check(anim_sprite->horizontal_orientation == 'L');
  mu_check(anim_sprite->pattern_idx == 5);
}

MU_TEST(test_animated_sprite_ground_kick) {
  anim_sprite->horizontal_orientation = 'R';
  anim_sprite->jump_status = 'G';
  anim_sprite->pos.x = 130;
  animated_sprite_kick(anim_sprite);
  mu_check(anim_sprite->pos.x == 130);
  mu_check(anim_sprite->horizontal_orientation == 'R');
  mu_check(anim_sprite->jump_status == 'G');
  mu_check(anim_sprite->pattern_idx == 13);

  anim_sprite->horizontal_orientation = 'L';
  anim_sprite->jump_status = 'G';
  anim_sprite->pos.x = 150;
  animated_sprite_kick(anim_sprite);
  mu_check(anim_sprite->pos.x == 150);
  mu_check(anim_sprite->horizontal_orientation == 'L');
  mu_check(anim_sprite->jump_status == 'G');
  mu_check(anim_sprite->pattern_idx == 14);
}

MU_TEST(test_animated_sprite_jump_kick) {
  anim_sprite->horizontal_orientation = 'R';
  anim_sprite->jump_status = 'U';
  anim_sprite->pos.x = 140;
  animated_sprite_kick(anim_sprite);
  mu_check(anim_sprite->pos.x == 140);
  mu_check(anim_sprite->horizontal_orientation == 'R');
  mu_check(anim_sprite->jump_status == 'U');
  mu_check(anim_sprite->pattern_idx == 17);

  anim_sprite->horizontal_orientation = 'L';
  anim_sprite->jump_status = 'U';
  anim_sprite->pos.x = 160;
  animated_sprite_kick(anim_sprite);
  mu_check(anim_sprite->pos.x == 160);
  mu_check(anim_sprite->horizontal_orientation == 'L');
  mu_check(anim_sprite->jump_status == 'U');
  mu_check(anim_sprite->pattern_idx == 18);
}


MU_TEST(test_animated_sprite_crouch_kick) {
  anim_sprite->horizontal_orientation = 'R';
  anim_sprite->jump_status = 'D';
  anim_sprite->pos.x = 140;
  animated_sprite_kick(anim_sprite);
  mu_check(anim_sprite->pos.x == 140);
  mu_check(anim_sprite->horizontal_orientation == 'R');
  mu_check(anim_sprite->jump_status == 'D');
  mu_check(anim_sprite->pattern_idx == 15);

  anim_sprite->horizontal_orientation = 'L';
  anim_sprite->jump_status = 'D';
  anim_sprite->pos.x = 160;
  animated_sprite_kick(anim_sprite);
  mu_check(anim_sprite->pos.x == 160);
  mu_check(anim_sprite->horizontal_orientation == 'L');
  mu_check(anim_sprite->jump_status == 'D');
  mu_check(anim_sprite->pattern_idx == 16);
}


MU_TEST(test_free_animated_sprite) {
  free_animated_sprite(anim_sprite);
}

MU_TEST_SUITE(animated_sprite_test_suite) {
  MU_SUITE_CONFIGURE(&test_animated_sprite_setup, &test_animated_sprite_teardown);
  MU_RUN_TEST(test_create_animated_sprite);
  MU_RUN_TEST(test_animated_sprite_move_right);
  MU_RUN_TEST(test_animated_sprite_move_left);
  MU_RUN_TEST(test_animated_sprite_move_down);
  MU_RUN_TEST(test_animated_sprite_move_up);
  MU_RUN_TEST(test_animated_sprite_ground_kick);
  MU_RUN_TEST(test_animated_sprite_jump_kick);
  MU_RUN_TEST(test_animated_sprite_crouch_kick);
  MU_RUN_TEST(test_free_animated_sprite);
}


