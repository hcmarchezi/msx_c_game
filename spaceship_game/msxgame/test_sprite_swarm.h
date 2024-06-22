#include "minunit/minunit.h"
#include "sprite_swarm.h"

MU_TEST(test_create_enemy_ships) {
  int rows = 3; int cols = 3;
  int xi = 50;  int yi = 50;
  int initial_sprite_id = 2;
  sprite_swarm* enemy_ships = create_enemy_ships(rows, cols, xi, yi, initial_sprite_id);

  mu_check(enemy_ships->array[0]->pos.x == 50); mu_check(enemy_ships->array[0]->pos.y == 50);
  mu_check(enemy_ships->array[1]->pos.x == 70); mu_check(enemy_ships->array[1]->pos.y == 50);
  mu_check(enemy_ships->array[2]->pos.x == 90); mu_check(enemy_ships->array[2]->pos.y == 50);
  mu_check(enemy_ships->array[3]->pos.x == 50); mu_check(enemy_ships->array[3]->pos.y == 70);
  mu_check(enemy_ships->array[4]->pos.x == 70); mu_check(enemy_ships->array[4]->pos.y == 70);
  mu_check(enemy_ships->array[5]->pos.x == 90); mu_check(enemy_ships->array[5]->pos.y == 70);
  mu_check(enemy_ships->array[6]->pos.x == 50); mu_check(enemy_ships->array[6]->pos.y == 90);
  mu_check(enemy_ships->array[7]->pos.x == 70); mu_check(enemy_ships->array[7]->pos.y == 90);
  mu_check(enemy_ships->array[8]->pos.x == 90); mu_check(enemy_ships->array[8]->pos.y == 90);

  char sprite_id = 2;
  for (int index = 0; index < 9; index++) {
      mu_check(enemy_ships->array[index]->sprite_id == sprite_id);
      mu_check(enemy_ships->array[index]->sprite_pattern == 3);
      mu_check(enemy_ships->array[index]->color == 15);
      sprite_id++;
  }

  free_enemy_ships(enemy_ships);
}

MU_TEST(test_move_enemy_ships) {
  int rows = 2; int cols = 2;
  int xi = 50;  int yi = 50;
  int initial_sprite_id = 2;
  sprite_swarm* enemy_ships = create_enemy_ships(rows, cols, xi, yi, initial_sprite_id);

  enemy_ships_move(enemy_ships, -1, -1);

  mu_check(enemy_ships->array[0]->pos.x == 49 && enemy_ships->array[0]->pos.y == 49);
  mu_check(enemy_ships->array[1]->pos.x == 69 && enemy_ships->array[1]->pos.y == 49);
  mu_check(enemy_ships->array[2]->pos.x == 49 && enemy_ships->array[2]->pos.y == 69);
  mu_check(enemy_ships->array[3]->pos.x == 69 && enemy_ships->array[3]->pos.y == 69);

  free_enemy_ships(enemy_ships);
}

unsigned int disIdx = 0;
unsigned int expected_x[] = { 50, 70, 50, 70 };
unsigned int expected_y[] = { 50, 50, 70, 70 };
unsigned int expected_sprite_id[] = {2, 3, 4, 5};

void swarm_test_put_sprite_16(unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern) {
  mu_check(sprite_id == expected_sprite_id[disIdx]);
  mu_check(x == expected_x[disIdx]);
  mu_check(y == expected_y[disIdx]);
  mu_check(color == 15);
  mu_check(sprite_pattern == 3);
  disIdx++;
}


MU_TEST(test_display_enemy_ships) {
  int rows = 2; int cols = 2;
  int xi = 50;  int yi = 50;
  int initial_sprite_id = 2;
  sprite_swarm* enemy_ships = create_enemy_ships(rows, cols, xi, yi, initial_sprite_id);

  unsigned char result = display_enemy_ships(enemy_ships, swarm_test_put_sprite_16);

  mu_check(result == 0);

  free_enemy_ships(enemy_ships);
}


MU_TEST_SUITE(sprite_swarm_test_suite) {
  MU_RUN_TEST(test_create_enemy_ships);
  MU_RUN_TEST(test_move_enemy_ships);
  MU_RUN_TEST(test_display_enemy_ships); 
}
