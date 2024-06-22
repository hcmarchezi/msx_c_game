#include "minunit/minunit.h"

#include "music_tones.h"


MU_TEST(test_create_music_tones) {
	music_tones tones;

	unsigned int channel_0_tones[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	unsigned int channel_1_tones[] = { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };

	create_music_tones(&tones, channel_0_tones, channel_1_tones, 10);

	mu_assert_int_eq(0, tones.index);
	mu_assert_int_eq(10, tones.count);

	for (int index = 0; index < tones.count; index++) {
		mu_assert_int_eq(channel_0_tones[index], tones.channel_0_tones[index]);
		mu_assert_int_eq(channel_1_tones[index], tones.channel_1_tones[index]);
	}
}


unsigned int stub_set_psg_reg_0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int stub_set_psg_reg_0_count = 0;
unsigned int stub_set_psg_reg_1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int stub_set_psg_reg_1_count = 0;
unsigned int stub_set_psg_reg_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int stub_set_psg_reg_2_count = 0;
unsigned int stub_set_psg_reg_3[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int stub_set_psg_reg_3_count = 0;
unsigned int stub_set_psg_reg_x[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int stub_set_psg_reg_x_count = 0;

void stub_set_psg(unsigned int reg, unsigned int val) {
	if (reg == 0) {
		stub_set_psg_reg_0[stub_set_psg_reg_0_count++] = val;
	} else if (reg == 1) {
		stub_set_psg_reg_1[stub_set_psg_reg_1_count++] = val;
	} else if (reg == 2) {
		stub_set_psg_reg_2[stub_set_psg_reg_2_count++] = val;
	} else if (reg == 3) {
		stub_set_psg_reg_3[stub_set_psg_reg_3_count++] = val;
	} else {
		stub_set_psg_reg_x[stub_set_psg_reg_x_count++] = val;
	}
}


MU_TEST(test_music_tones_play_tone_and_next) {
	music_tones tones;

	unsigned int channel_0_tones[] = { 10, 11, 12 };
	unsigned int channel_1_tones[] = { 20, 21, 22 };

	create_music_tones(&tones, channel_0_tones, channel_1_tones, 3);

	unsigned int channel_0_tone, channel_1_tone;

	music_tones_play_tone(&tones, 0, stub_set_psg);
	music_tones_play_tone(&tones, 1, stub_set_psg);

	music_tones_next_tone(&tones);
	music_tones_play_tone(&tones, 0, stub_set_psg);
	music_tones_play_tone(&tones, 1, stub_set_psg);

	music_tones_next_tone(&tones);
	music_tones_play_tone(&tones, 0, stub_set_psg);
	music_tones_play_tone(&tones, 1, stub_set_psg);

	music_tones_next_tone(&tones);
	music_tones_play_tone(&tones, 0, stub_set_psg);
	music_tones_play_tone(&tones, 1, stub_set_psg);

	mu_assert_int_eq(10, stub_set_psg_reg_0[0]);
	mu_assert_int_eq( 0, stub_set_psg_reg_1[0]);
	mu_assert_int_eq(20, stub_set_psg_reg_2[0]);
	mu_assert_int_eq( 0, stub_set_psg_reg_3[0]);

	mu_assert_int_eq(11, stub_set_psg_reg_0[1]);
	mu_assert_int_eq( 0, stub_set_psg_reg_1[1]);
	mu_assert_int_eq(21, stub_set_psg_reg_2[1]);
	mu_assert_int_eq( 0, stub_set_psg_reg_3[1]);

	mu_assert_int_eq(12, stub_set_psg_reg_0[2]);
	mu_assert_int_eq( 0, stub_set_psg_reg_1[2]);
	mu_assert_int_eq(22, stub_set_psg_reg_2[2]);
	mu_assert_int_eq( 0, stub_set_psg_reg_3[2]);

	mu_assert_int_eq(10, stub_set_psg_reg_0[3]);
	mu_assert_int_eq( 0, stub_set_psg_reg_1[3]);
	mu_assert_int_eq(20, stub_set_psg_reg_2[3]);
	mu_assert_int_eq( 0, stub_set_psg_reg_3[3]);	
}

MU_TEST_SUITE(music_tones_test_suite) {
	MU_RUN_TEST(test_create_music_tones);
	MU_RUN_TEST(test_music_tones_play_tone_and_next);
}
