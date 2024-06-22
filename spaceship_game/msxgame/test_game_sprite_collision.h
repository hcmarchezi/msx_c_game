#include "minunit/minunit.h"
#include "test_helper.h"

#include "game_sprite.h"
#include "game_sprite_collision.h"


MU_TEST(test_game_sprite_collision) {
	unsigned int color = 10;
    unsigned int sprite_pattern = 0;
    int velocity = 1;

	game_sprite sp1;
	int x1 = 100;
	int y1 = 50;
	create_game_sprite(&sp1, 0, x1, y1, color, sprite_pattern, velocity);

	game_sprite sp2;
	int x2 = 100;
	int y2 = 55;
	create_game_sprite(&sp2, 1, x2, y2, color, sprite_pattern, velocity);

	game_sprite sp3;
	int x3 = 150;
	int y3 = 50;
	create_game_sprite(&sp3, 2, x3, y3, color, sprite_pattern, velocity);

	game_sprite sp4;
	int x4 = 100;
	int y4 = 100;
	create_game_sprite(&sp4, 3, x4, y4, color, sprite_pattern, velocity);

	game_sprite sp5;
	int x5 = 150;
	int y5 = 150;
	create_game_sprite(&sp5, 4, x5, y5, color, sprite_pattern, velocity);

	mu_check(detect_sprite_collision(&sp1, &sp2) == 1);
	mu_check(detect_sprite_collision(&sp1, &sp3) == 0);
	mu_check(detect_sprite_collision(&sp1, &sp4) == 0);
	mu_check(detect_sprite_collision(&sp1, &sp5) == 0);
}


MU_TEST_SUITE(game_sprite_collision_test_suite) {
  	MU_RUN_TEST(test_game_sprite_collision);
}