#include "minunit/minunit.h"
#include "animation_sprite.h"
#include "common_sprite.h"

#include<stdio.h>

animation_sprite* animation = 0;

unsigned int patterns[] = { 15, 16, 17, 16, 15 };
unsigned int colors[]   = {  9, 10, 11, 10,  9 };

noise_instruction** sound_instrs = 0;

void test_animation_sprite_setup(void) { 
	/* Nothing */ 
	sound_instrs = (noise_instruction**)malloc(5 * sizeof(noise_instruction*));

	sound_instrs[0] = create_sound_instr(6, 10, 8);
	sound_instrs[1] = create_sound_instr(6, 15, 6);
	sound_instrs[2] = create_sound_instr(6, 20, 4);
	sound_instrs[3] = create_sound_instr(6, 25, 2);
	sound_instrs[4] = create_sound_instr(6, 30, 0);
}

void test_animation_sprite_teardown(void) { 
	/* Nothing */
}


MU_TEST(test_create_animation_sprite) {
	position pos; pos.x = 100; pos.y = 50;
	unsigned int sprite_id = 5;
	unsigned int pattern_count = 5;

	animation = create_animation_sprite(pos, sprite_id, patterns, colors, pattern_count, sound_instrs);

	mu_check(animation->pos.x == 100);
	mu_check(animation->pos.y == 50);
	mu_check(animation->sprite_id == 5);
	mu_check(animation->pattern_count == 5);
	mu_check(animation->pattern_idx == 0);
	
	mu_check(animation->patterns[0] == 15);
	mu_check(animation->patterns[1] == 16);
	mu_check(animation->patterns[2] == 17);
	mu_check(animation->patterns[3] == 16);
	mu_check(animation->patterns[4] == 15);

	mu_check(animation->colors[0] == 9);
	mu_check(animation->colors[1] == 10);
	mu_check(animation->colors[2] == 11);
	mu_check(animation->colors[3] == 10);
	mu_check(animation->colors[4] == 9);
}

MU_TEST(test_next_pattern_animation_sprite) {
	animation->pattern_idx = 0;

	mu_check(animation_sprite_has_next_pattern(animation) == 0x01);
	animation_sprite_next_pattern(animation);
	mu_check(animation->pattern_idx == 1);

	mu_check(animation_sprite_has_next_pattern(animation) == 0x01);
	animation_sprite_next_pattern(animation);
	mu_check(animation->pattern_idx == 2);

	mu_check(animation_sprite_has_next_pattern(animation) == 0x01);
	animation_sprite_next_pattern(animation);
	mu_check(animation->pattern_idx == 3);

	mu_check(animation_sprite_has_next_pattern(animation) == 0x01);
	animation_sprite_next_pattern(animation);
	mu_check(animation->pattern_idx == 4);

	mu_check(animation_sprite_has_next_pattern(animation) == 0x00);
}

void test_put_sprite_16_idx0(unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern) {
	mu_check(sprite_id == 5);
	mu_check(x == 100);
	mu_check(y == 50);
	mu_check(color == 9);
	mu_check(sprite_pattern == 15);
}

void test_put_sprite_16_idx2(unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern) {
	mu_check(sprite_id == 5);
	mu_check(x == 100);
	mu_check(y == 50);
	mu_check(color == 11);
	mu_check(sprite_pattern == 17);
}

MU_TEST(test_display_animation_sprite) {
	animation->pattern_idx = 0;
	animation_sprite_display(animation, test_put_sprite_16_idx0);
	animation->pattern_idx = 2;
	animation_sprite_display(animation, test_put_sprite_16_idx2);
}

int test_set_psg_idx = 0;
unsigned int expected_regs[] = {  6, 10,  6, 10,  6, 10,  6, 10,  6, 10 };
unsigned int expected_vals[] = { 10,  8, 15,  6, 20,  4, 25,  2, 30,  0 };

void test_set_psg(unsigned int reg, unsigned int val) {
	mu_check(reg == expected_regs[test_set_psg_idx]);
	mu_check(val == expected_vals[test_set_psg_idx]);
	test_set_psg_idx++;
}

MU_TEST(test_make_sound_animation_sprite) {
	animation->pattern_idx = 0;
	animation_sprite_sound(animation, test_set_psg);

	animation_sprite_next_pattern(animation);
	animation_sprite_sound(animation, test_set_psg);

	animation_sprite_next_pattern(animation);
	animation_sprite_sound(animation, test_set_psg);

	animation_sprite_next_pattern(animation);
	animation_sprite_sound(animation, test_set_psg);

	animation_sprite_next_pattern(animation);
	animation_sprite_sound(animation, test_set_psg);
}

MU_TEST_SUITE(animation_sprite_test_suite) {
	MU_SUITE_CONFIGURE(&test_animation_sprite_setup, &test_animation_sprite_teardown);
  	MU_RUN_TEST(test_create_animation_sprite);
  	MU_RUN_TEST(test_next_pattern_animation_sprite);
  	MU_RUN_TEST(test_display_animation_sprite);
  	MU_RUN_TEST(test_make_sound_animation_sprite);
}