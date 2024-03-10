#include "minunit/minunit.h"
#include "test_helper.h"

#include "game_sprite.h"
#include "game_sprite_collision.h"


MU_TEST(test_game_sprite_collision) {
	unsigned int sprite_id = 10;
	unsigned int color = 10;
	unsigned int sprite_pattern = 10;
	unsigned int velocity = 1;

	game_sprite ship_1;
	create_game_sprite(&ship_1, sprite_id, 100, 100, color, sprite_pattern, velocity);

	game_sprite ship_2;
	create_game_sprite(&ship_2, sprite_id + 1, 100, 100, color, sprite_pattern, velocity);
	game_sprite ship_3;
	create_game_sprite(&ship_3, sprite_id + 2,  50,  50, color, sprite_pattern, velocity);
	game_sprite ship_4;
	create_game_sprite(&ship_4, sprite_id + 3, 110, 110, color, sprite_pattern, velocity);
	game_sprite ship_5;
	create_game_sprite(&ship_5, sprite_id + 4, 115, 100, color, sprite_pattern, velocity);
	game_sprite ship_6;
	create_game_sprite(&ship_6, sprite_id + 5, 100, 115, color, sprite_pattern, velocity);
	game_sprite ship_7;
	create_game_sprite(&ship_7, sprite_id + 6, 132, 132, color, sprite_pattern, velocity);
	game_sprite ship_8;
	create_game_sprite(&ship_8, sprite_id + 7, 150, 150, color, sprite_pattern, velocity);
    game_sprite ship_9;
    create_game_sprite(&ship_9, sprite_id + 8,  90,  90, color, sprite_pattern, velocity);

    game_sprite* to_ships[8] = { &ship_2, &ship_3, &ship_4, &ship_5, &ship_6, &ship_7, &ship_8, &ship_9 };

    sprite_collision collision;
    create_sprite_collision(&collision, &ship_1, to_ships, 8);
    
    mu_check(collision.from->x == 100);
    mu_check(collision.from->y == 100);
    mu_check(collision.from->sprite_id == 10);

	sprite_collision_check(&collision);

	mu_check(collision.collision[0] == 1);
	mu_check(collision.collision[2] == 1);
	mu_check(collision.collision[3] == 1);
	mu_check(collision.collision[4] == 1);
	mu_check(collision.collision[7] == 1);

	mu_check(collision.collision[1] == 0);
	mu_check(collision.collision[5] == 0);
	mu_check(collision.collision[6] == 0);

	sprite_collision_clear(&collision);

	for (int index=0; index < 16; index++) {
		mu_check(collision.collision[index] == 0);
	}
}


MU_TEST_SUITE(game_sprite_collision_test_suite) {
  	MU_RUN_TEST(test_game_sprite_collision);
}