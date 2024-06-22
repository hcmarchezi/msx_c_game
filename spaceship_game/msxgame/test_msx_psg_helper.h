#include "minunit/minunit.h"

#include "msx_psg_helper.h"

MU_TEST(test_convert_notes_to_tones) {
	char channel_0_notes[] = "CDEFGABC";
	unsigned int note_count = 8;
	unsigned int channel_0_tones[note_count];

	int octave = 4;
	map_notes_to_tones(octave, channel_0_notes, note_count, channel_0_tones);

	mu_assert_int_eq(0x1AC, channel_0_tones[0]); // C
	mu_assert_int_eq(0x17D, channel_0_tones[1]); // D
	mu_assert_int_eq(0x153, channel_0_tones[2]); // E
	mu_assert_int_eq(0x140, channel_0_tones[3]); // F
	mu_assert_int_eq(0x11D, channel_0_tones[4]); // G
	mu_assert_int_eq(0x0FE, channel_0_tones[5]); // A
	mu_assert_int_eq(0x0E3, channel_0_tones[6]); // B
	mu_assert_int_eq(0x1AC, channel_0_tones[7]); // C
}

MU_TEST_SUITE(msx_psg_helper_test_suite) {
	MU_RUN_TEST(test_convert_notes_to_tones);
}

