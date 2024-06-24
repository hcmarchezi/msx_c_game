#include "minunit/minunit.h"
#include "ship_sequence.h"

#include "game_sprite.h"
#include "test_helper.h"

void create_ship_sequence(ship_sequence* seq) {
	seq->ship_count = 3;
	create_game_sprite(&seq->ships[0], 0, 120, -50, 12, 1, 1);
	create_game_sprite(&seq->ships[1], 1,  80, -30, 12, 1, 1);
	create_game_sprite(&seq->ships[2], 2, 180, -40, 12, 1, 1);

	for(int idx=0; idx < 32; idx++) {
		seq->x_seq[idx] = 2;
		seq->y_seq[idx] = 1;
	}

	seq->x_seq_idx[0] = 0;
	seq->x_seq_idx[1] = 16;
	seq->x_seq_idx[2] = 31;

	seq->y_seq_idx[0] = 10;
	seq->y_seq_idx[1] = 26;
	seq->y_seq_idx[2] = 9;

	seq->end_of_sequence = 0;
}


MU_TEST(test_ship_sequence_update_position) {
	ship_sequence seq;
	create_ship_sequence(&seq);


	ship_sequence_update_position(&seq);

	mu_assert(seq.ships[0].x, 122);
	mu_assert(seq.ships[0].y, -49);

	mu_assert(seq.ships[1].x, 82);
	mu_assert(seq.ships[1].y, -29);

	mu_assert(seq.ships[2].x, 182);
	mu_assert(seq.ships[2].y, -39);

	mu_assert(seq.x_seq_idx, 1);
	mu_assert(seq.x_seq_idx, 17);
	mu_assert(seq.x_seq_idx, 0);

	mu_assert(seq.x_seq_idx, 11);
	mu_assert(seq.x_seq_idx, 27);
	mu_assert(seq.x_seq_idx, 10);
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
	ship_sequence seq;
	create_ship_sequence(&seq);

	ship_sequence_display(&seq, fake_put_sprite_16);

	//printf("fake_sprite_id=%d ", fake_sprite_id);
	//printf("fake_sprite_id[0]=%d \n", fake_sprite_id[0]);
	//printf("fake_sprite_id[1]=%d \n", fake_sprite_id[1]);
	//printf("fake_sprite_id[2]=%d \n", fake_sprite_id[2]);

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
  MU_RUN_TEST(test_ship_sequence_update_position);
  MU_RUN_TEST(test_ship_sequence_display);
}