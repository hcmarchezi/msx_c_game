#include "minunit/minunit.h"
#include "test_helper.h"

#include "game_sprite.h"


unsigned int* test_explosion_pattern[] = { 10, 11, 12, 13, 12, 11, 10 };


game_sprite create_test_game_sprite(int x, int y) {
	unsigned int sprite_id = 0;
	unsigned int color = 15;
	unsigned int sprite_pattern = 0;
	int velocity = 1;
	unsigned int* explosion_pattern = test_explosion_pattern;
	unsigned char explosion_count = 7;

	game_sprite sprite;
	init_game_sprite(&sprite, sprite_id, x, y, color, sprite_pattern, velocity, explosion_pattern, explosion_count);

	return sprite;
}


MU_TEST(test_define_sprite_pattern) {
	init_vpoke_func();

	const unsigned char sprite_pattern[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
	};
	int sprite_pattern_id = 4;
	define_sprite_pattern(sprite_pattern_id, sprite_pattern, &vpoke_func);

	for(int index=0; index < 32; index++) {
		mu_assert_int_eq(index + 0x3880, vpoke_mem[index]);
		mu_assert_int_eq(index, vpoke_val[index]);
	}
}


MU_TEST(test_init_game_sprite) {
	unsigned int sprite_id = 5;
	int pos_x = 100;
	int pos_y = 50;
	unsigned int color = 13;
	unsigned int sprite_pattern = 2;
	int velocity = 1;
	unsigned int* explosion_pattern = test_explosion_pattern;
	unsigned char explosion_count = 7;

	game_sprite ship;
	init_game_sprite(&ship, sprite_id, pos_x, pos_y, color, sprite_pattern, velocity, explosion_pattern, explosion_count);

	mu_check(ship.sprite_id == 5);
	mu_check(ship.x == 100);
	mu_check(ship.y == 50);
	mu_check(ship.color == 13);
	mu_check(ship.sprite_pattern == 2);
	mu_check(ship.velocity == 1);
	mu_check(ship.status == 'A');
	mu_check(ship.explosion_idx == 0);
	mu_check(ship.explosion_pattern == explosion_pattern);
	mu_check(ship.explosion_count == 7);
}


MU_TEST(test_game_sprite_move) {
	game_sprite ship = create_test_game_sprite(100, 50);

	game_sprite_move(&ship, 1);
	mu_check(ship.x == 100);
	mu_check(ship.y == 49);

	game_sprite_move(&ship, 2);
	mu_check(ship.x == 101);
	mu_check(ship.y == 48);

	game_sprite_move(&ship, 3);
	mu_check(ship.x == 102);
	mu_check(ship.y == 48);

	game_sprite_move(&ship, 4);
	mu_check(ship.x == 103);
	mu_check(ship.y == 49);

	game_sprite_move(&ship, 5);
	mu_check(ship.x == 103);
	mu_check(ship.y == 50);

	game_sprite_move(&ship, 6);
	mu_check(ship.x == 102);
	mu_check(ship.y == 51);

	game_sprite_move(&ship, 7);
	mu_check(ship.x == 101);
	mu_check(ship.y == 51);

	game_sprite_move(&ship, 8);
	mu_check(ship.x == 100);
	mu_check(ship.y == 50);
}


MU_TEST(test_game_sprite_get_position) {
	game_sprite ship = create_test_game_sprite(100, 50);
	int pos_x, pos_y;
	game_sprite_get_position(&ship, &pos_x, &pos_y);
	mu_check(pos_x == 100);
	mu_check(pos_y == 50);
}

unsigned int test_sprite_id = 999;
int test_x = 999;
int test_y = 999;
unsigned int test_sprite_pattern = 999;
unsigned int test_color = 999;
void test_game_sprite_put_sprite_16(unsigned int sprite_id, int x, int y, unsigned int sprite_pattern, unsigned int color) {
	test_sprite_id = sprite_id;
	test_x = x;
	test_y = y;
	test_sprite_pattern = sprite_pattern;
	test_color = color;
}


MU_TEST(test_game_sprite_display) {
	unsigned int sprite_id = 5;
	unsigned int pos_x = 100;
	unsigned int pos_y = 50;
	unsigned int color = 13;
	unsigned int sprite_pattern = 2;
	unsigned int velocity = 1;
	unsigned int* explosion_pattern = 0;
	unsigned char explosion_count = 0;

	game_sprite ship;
	init_game_sprite(&ship, sprite_id, pos_x, pos_y, color, sprite_pattern, velocity, explosion_pattern, explosion_count);

	game_sprite_display(&ship, &test_game_sprite_put_sprite_16);

	mu_check(test_sprite_id == 5);
	mu_check(test_x == 100);
	mu_check(test_y == 50);
	mu_check(test_color == 13);
	mu_check(test_sprite_pattern == 2);
}


MU_TEST(test_game_sprite_explosion) {

	printf("\n");

	unsigned int sprite_id = 5;
	unsigned int pos_x = 100;
	unsigned int pos_y = 50;
	unsigned int color = 13;
	unsigned int sprite_pattern = 2;
	unsigned int velocity = 1;
	unsigned int explosion_pattern[] = {10, 11, 12, 13, 12, 11, 10};
	unsigned char explosion_count = 7;	

	/////// test status active (A)
	game_sprite ship;
	init_game_sprite(&ship, sprite_id, pos_x, pos_y, color, sprite_pattern, velocity, explosion_pattern, explosion_count);

	game_sprite_display(&ship, &test_game_sprite_put_sprite_16);
	mu_check(ship.status == 'A');
	mu_check(test_sprite_id == 5);
	mu_check(test_x == 100);
	mu_check(test_y == 50);
	mu_check(test_color == 13);
	mu_check(test_sprite_pattern == 2);

	// set explosion mode
	game_sprite_set_explosion_mode(&ship);

	/////// test status explosion (E)	
	for(int idx=0; idx < 7; idx++) {
		game_sprite_display(&ship, &test_game_sprite_put_sprite_16);
		mu_check(ship.status == 'E');
		mu_check(test_sprite_id == 5);
		mu_check(test_x == 100);
		mu_check(test_y == 50);
		mu_check(test_color == 10);
		mu_check(test_sprite_pattern == explosion_pattern[idx]);
	}

	/////// test status destroyed (D)
	game_sprite_display(&ship, &test_game_sprite_put_sprite_16);
	mu_check(ship.status == 'D');
	mu_check(test_sprite_id == 5);
	mu_assert(test_x, 256);
	mu_assert(test_y, 200);
	mu_check(test_color == 10);
	mu_assert(test_sprite_pattern, 10);
}



MU_TEST_SUITE(game_sprite_test_suite) {
	MU_RUN_TEST(test_define_sprite_pattern);
  	MU_RUN_TEST(test_init_game_sprite);
  	MU_RUN_TEST(test_game_sprite_move);
  	MU_RUN_TEST(test_game_sprite_get_position);
  	MU_RUN_TEST(test_game_sprite_display);
  	MU_RUN_TEST(test_game_sprite_explosion);
}
