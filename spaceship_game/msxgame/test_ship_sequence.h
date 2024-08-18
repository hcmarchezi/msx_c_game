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

MU_TEST(test_ship_sequence_init) {
	int x_seq[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int y_seq[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int x_seq_idx[] = { 0,  1,  2};
	int y_seq_idx[] = {10, 11, 12};

	ship_sequence seq;
	
	seq.ships[0] = new_game_sprite(0, 120, -50, 12, 1, 1, 0, 0);
	seq.ships[1] = new_game_sprite(1,  80, -30, 12, 1, 1, 0, 0);
	seq.ships[2] = new_game_sprite(2, 180, -40, 12, 1, 1, 0, 0);
	seq.ship_count = 3;
	for (int index=0; index < seq.ship_count; index++) {
		seq.x_seq_idx[index] = x_seq_idx[index]; 
		seq.y_seq_idx[index] = y_seq_idx[index]; 
	}

	seq.seq_count = 10;
	seq.x_seq = &x_seq;
	seq.y_seq = &y_seq;
	mu_assert_int_eq(3, seq.ship_count);

	mu_assert_int_eq(seq.ships[0]->sprite_id, 0);
	mu_assert_int_eq(seq.ships[0]->x, 120);
	mu_assert_int_eq(seq.ships[0]->y, -50);
	mu_assert_int_eq(seq.ships[0]->color, 12);
	mu_assert_int_eq(seq.ships[0]->sprite_pattern, 1);
	mu_assert_int_eq(seq.ships[0]->velocity, 1);

	mu_assert_int_eq(seq.ships[1]->sprite_id, 1);
	mu_assert_int_eq(seq.ships[1]->x,  80);
	mu_assert_int_eq(seq.ships[1]->y, -30);
	mu_assert_int_eq(seq.ships[1]->color, 12);
	mu_assert_int_eq(seq.ships[1]->sprite_pattern, 1);
	mu_assert_int_eq(seq.ships[1]->velocity, 1);
	
	mu_assert_int_eq(seq.ships[2]->sprite_id, 2);
	mu_assert_int_eq(seq.ships[2]->x, 180);
	mu_assert_int_eq(seq.ships[2]->y, -40);
	mu_assert_int_eq(seq.ships[2]->color, 12);
	mu_assert_int_eq(seq.ships[2]->sprite_pattern, 1);
	mu_assert_int_eq(seq.ships[2]->velocity, 1);

	for (int idx=0; idx < seq.seq_count; idx++) {
		mu_assert_int_eq(idx, seq.x_seq[idx]);
		mu_assert_int_eq(idx, seq.y_seq[idx]);
	}

	for (int idx=0; idx < seq.ship_count; idx++) {
		mu_assert_int_eq(idx,      seq.x_seq_idx[idx]);
		mu_assert_int_eq(idx + 10, seq.y_seq_idx[idx]);
	}
}

MU_TEST(test_ship_sequence_update_position) {
	int x_seq_idx[] = {0, 2, 4};
	int y_seq_idx[] = {4, 3, 0};

	int x_seq[] = {2, 2, 2, 2, 2};
	int y_seq[] = {1, 1, 1, 1, 1};

	ship_sequence seq;
	seq.ship_count = 3;
	seq.ships[0] = new_game_sprite(0, 120, -50, 12, 1, 1, 0, 0);
	seq.ships[1] = new_game_sprite(1,  80, -30, 12, 1, 1, 0, 0);
	seq.ships[2] = new_game_sprite(2, 180, -40, 12, 1, 1, 0, 0);
	for (int index=0; index < seq.ship_count; index++) {
		seq.x_seq_idx[index] = x_seq_idx[index];
		seq.y_seq_idx[index] = y_seq_idx[index];
	}
	seq.seq_count = 5;
	seq.x_seq = x_seq;
	seq.y_seq = y_seq;

	ship_sequence_update_position(&seq);

	mu_assert_int_eq(seq.ships[0]->x, 122);
	mu_assert_int_eq(seq.ships[0]->y, -49);

	mu_assert_int_eq(seq.ships[1]->x, 82);
	mu_assert_int_eq(seq.ships[1]->y, -29);

	mu_assert_int_eq(seq.ships[2]->x, 182);
	mu_assert_int_eq(seq.ships[2]->y, -39);

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

	int x_seq_idx[] = {0, 1, 2};
	int y_seq_idx[] = {2, 1, 0};

	int x_seq[] = {0, 0, 0, 0, 0};
	int y_seq[] = {1, 1, 1, 1, 1};

	ship_sequence seq;
	seq.ships[0] = new_game_sprite(0, 120, -50, 12, 1, 1, 0, 0);
	seq.ships[1] = new_game_sprite(1,  80, -30, 12, 1, 1, 0, 0);
	seq.ships[2] = new_game_sprite(2, 180, -40, 12, 1, 1, 0, 0);
	seq.ship_count = 3;
	for(int index=0; index < seq.ship_count; index++) {
		seq.x_seq_idx[index] = x_seq_idx[index];
		seq.y_seq_idx[index] = y_seq_idx[index];
	}
	

	seq.x_seq = x_seq;
	seq.y_seq = y_seq;
	seq.seq_count = 5;

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

	mu_assert_int_eq(fake_sprite_y[0], -50);
	mu_assert_int_eq(fake_sprite_y[1], -30);
	mu_assert_int_eq(fake_sprite_y[2], -40);
}

MU_TEST_SUITE(ship_sequence_test_suite) {
  MU_RUN_TEST(test_ship_sequence_init);
  MU_RUN_TEST(test_ship_sequence_update_position);
  MU_RUN_TEST(test_ship_sequence_display);
}