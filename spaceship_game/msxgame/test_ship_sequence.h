#include "minunit/minunit.h"
#include "ship_sequence.h"

#include "game_sprite.h"
#include "test_helper.h"

game_sprite ship_sequence_create_test_game_sprite(
		unsigned int sprite_id, int x, int y, 
		unsigned int color, unsigned int sprite_pattern, int velocity,
		unsigned int* explosion_pattern, unsigned char explosion_count) {
	game_sprite sprite;
	init_game_sprite(&sprite, sprite_id, x, y, color, sprite_pattern, velocity, explosion_pattern, explosion_count);
	return sprite;
}

ship_sequence create_test_ship_sequence(
		game_sprite* ships,
    unsigned char ship_count,
    int* x_seq, int* y_seq, unsigned char seq_count,
    int* x_seq_idx, int* y_seq_idx) {

	ship_sequence seq;

	init_ship_sequence(
    &seq,
    ships, ship_count,
    x_seq, y_seq, seq_count,
    x_seq_idx, y_seq_idx);

	return seq;
}


MU_TEST(test_ship_sequence_init) {
	game_sprite enemy_ships[] = { 
		ship_sequence_create_test_game_sprite(0, 120, -50, 12, 1, 1, 0, 0), 
		ship_sequence_create_test_game_sprite(1,  80, -30, 12, 1, 1, 0, 0), 
		ship_sequence_create_test_game_sprite(2, 180, -40, 12, 1, 1, 0, 0)
	};

	int x_seq[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int y_seq[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int x_seq_idx[] = { 0,  1,  2};
	int y_seq_idx[] = {10, 11, 12};

	ship_sequence seq;

	 init_ship_sequence(
	 		&seq,
	    &enemy_ships, 3,
	    &x_seq, &y_seq, 10,
	    &x_seq_idx, &y_seq_idx);

	mu_assert_int_eq(3, seq.ship_count);

	mu_assert_int_eq(seq.ships[0].sprite_id, enemy_ships[0].sprite_id);
	mu_assert_int_eq(seq.ships[0].x, enemy_ships[0].x);
	mu_assert_int_eq(seq.ships[0].y, enemy_ships[0].y);
	mu_assert_int_eq(seq.ships[0].color, enemy_ships[0].color);
	mu_assert_int_eq(seq.ships[0].sprite_pattern, enemy_ships[0].sprite_pattern);
	mu_assert_int_eq(seq.ships[0].velocity, enemy_ships[0].velocity);

	mu_assert_int_eq(seq.ships[1].sprite_id, enemy_ships[1].sprite_id);
	mu_assert_int_eq(seq.ships[1].x, enemy_ships[1].x);
	mu_assert_int_eq(seq.ships[1].y, enemy_ships[1].y);
	mu_assert_int_eq(seq.ships[1].color, enemy_ships[1].color);
	mu_assert_int_eq(seq.ships[1].sprite_pattern, enemy_ships[1].sprite_pattern);
	mu_assert_int_eq(seq.ships[1].velocity, enemy_ships[1].velocity);
	
	mu_assert_int_eq(seq.ships[2].sprite_id, enemy_ships[2].sprite_id);
	mu_assert_int_eq(seq.ships[2].x, enemy_ships[2].x);
	mu_assert_int_eq(seq.ships[2].y, enemy_ships[2].y);
	mu_assert_int_eq(seq.ships[2].color, enemy_ships[2].color);
	mu_assert_int_eq(seq.ships[2].sprite_pattern, enemy_ships[2].sprite_pattern);
	mu_assert_int_eq(seq.ships[2].velocity, enemy_ships[2].velocity);

	for (int idx=0; idx < seq.seq_count; idx++) {
		mu_assert_int_eq(idx, seq.x_seq[idx]);
		mu_assert_int_eq(idx, seq.y_seq[idx]);
	}

	for (int idx=0; idx < seq.ship_count; idx++) {
		mu_assert_int_eq(idx, seq.x_seq_idx[idx]);
		mu_assert_int_eq(idx + 10, seq.y_seq_idx[idx]);
	}
}

MU_TEST(test_ship_sequence_update_position) {
	game_sprite ships[] = { 
		ship_sequence_create_test_game_sprite(0, 120, -50, 12, 1, 1, 0, 0), 
		ship_sequence_create_test_game_sprite(1,  80, -30, 12, 1, 1, 0, 0), 
		ship_sequence_create_test_game_sprite(2, 180, -40, 12, 1, 1, 0, 0) 
	};
	int x_seq_idx[] = {0, 2, 4};
	int y_seq_idx[] = {4, 3, 0};
	unsigned char ship_count = 3;

	int x_seq[] = {2, 2, 2, 2, 2};
	int y_seq[] = {1, 1, 1, 1, 1};
	unsigned char seq_count = 5;

	ship_sequence seq = create_test_ship_sequence(
		&ships,
    ship_count,    
    &x_seq, 
    &y_seq, 
    seq_count,    
    &x_seq_idx, 
    &y_seq_idx);

	ship_sequence_update_position(&seq);

	mu_assert_int_eq(seq.ships[0].x, 122);
	mu_assert_int_eq(seq.ships[0].y, -49);

	mu_assert_int_eq(seq.ships[1].x, 82);
	mu_assert_int_eq(seq.ships[1].y, -29);

	mu_assert_int_eq(seq.ships[2].x, 182);
	mu_assert_int_eq(seq.ships[2].y, -39);

	mu_assert_int_eq(seq.x_seq_idx[0], 1);
	mu_assert_int_eq(seq.x_seq_idx[1], 3);
	mu_assert_int_eq(seq.x_seq_idx[2], 0);

	mu_assert_int_eq(seq.y_seq_idx[0], 0);
	mu_assert_int_eq(seq.y_seq_idx[1], 4);
	mu_assert_int_eq(seq.y_seq_idx[2], 1);
}

unsigned int fake_sprite_id[] = {0, 0, 0, 0, 0, 0};
unsigned int fake_sprite_pattern[] = {0, 0, 0, 0, 0, 0};
unsigned int fake_sprite_color[] = {0, 0, 0, 0, 0, 0};
int fake_sprite_x[] = {0, 0, 0, 0, 0, 0};
int fake_sprite_y[] = {0, 0, 0, 0, 0, 0};
int fake_sprite_idx = 0;
void fake_put_sprite_16(unsigned int sprite_id, int x, int y, unsigned int sprite_pattern, unsigned int color) {
	fake_sprite_id[fake_sprite_idx] = sprite_id;
	fake_sprite_x[fake_sprite_idx] = x;
	fake_sprite_y[fake_sprite_idx] = y;
	fake_sprite_pattern[fake_sprite_idx] = sprite_pattern;
	fake_sprite_color[fake_sprite_idx] = color;
	fake_sprite_idx++;
}

MU_TEST(test_ship_sequence_display) {
	game_sprite sp1;
	game_sprite sp2;
	game_sprite sp3;

	game_sprite ships[] = {
		ship_sequence_create_test_game_sprite(0, 120, -50, 12, 1, 1, 0, 0),
		ship_sequence_create_test_game_sprite(1,  80, -30, 12, 1, 1, 0, 0),
		ship_sequence_create_test_game_sprite(2, 180, -40, 12, 1, 1, 0, 0)
	};
	int x_seq_idx[] = {0, 1, 2};
	int y_seq_idx[] = {2, 1, 0};
	unsigned char ship_count = 3;

	int x_seq[] = {0, 0, 0, 0, 0};
	int y_seq[] = {1, 1, 1, 1, 1};
	unsigned char seq_count = 5;

	ship_sequence seq = create_test_ship_sequence(
		&ships,
    ship_count,    
    &x_seq, 
    &y_seq, 
    seq_count,    
    &x_seq_idx, 
    &y_seq_idx);

	ship_sequence_display(&seq, fake_put_sprite_16);

	mu_assert_int_eq(fake_sprite_id[0], 0);
	mu_assert_int_eq(fake_sprite_id[1], 1);
	mu_assert_int_eq(fake_sprite_id[2], 2);

	mu_assert_int_eq(fake_sprite_pattern[0], 1);
	mu_assert_int_eq(fake_sprite_pattern[1], 1);
	mu_assert_int_eq(fake_sprite_pattern[2], 1);

	mu_assert_int_eq(fake_sprite_color[0], 12);
	mu_assert_int_eq(fake_sprite_color[1], 12);
	mu_assert_int_eq(fake_sprite_color[2], 12);

	mu_assert_int_eq(fake_sprite_x[0], 120);
	mu_assert_int_eq(fake_sprite_x[1], 80);
	mu_assert_int_eq(fake_sprite_x[2], 180);

	mu_assert_int_eq(fake_sprite_y[0], -49);
	mu_assert_int_eq(fake_sprite_y[1], -29);
	mu_assert_int_eq(fake_sprite_y[2], -39);
}

MU_TEST_SUITE(ship_sequence_test_suite) {
  MU_RUN_TEST(test_ship_sequence_init);
  MU_RUN_TEST(test_ship_sequence_update_position);
  MU_RUN_TEST(test_ship_sequence_display);
}