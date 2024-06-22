#include "minunit/minunit.h"
#include "simple_music.h"

MU_TEST(test_create_simple_music) {
	simple_music music;
	unsigned int channel_0_tones[] = { 0x0000, 0x4000, 0x8000 };
	unsigned int channel_1_tones[] = { 0x1000, 0x2000, 0x3000 };
	unsigned int size = 3;

	simple_music_create(&music, channel_0_tones, channel_1_tones, size);

	mu_assert_int_eq(3, music.size);
	mu_assert_int_eq(0, music.idx);

	mu_assert_int_eq(0x0000, music.channel_0_tones[0]);
	mu_assert_int_eq(0x4000, music.channel_0_tones[1]);
	mu_assert_int_eq(0x8000, music.channel_0_tones[2]);

	mu_assert_int_eq(0x1000, music.channel_1_tones[0]);
	mu_assert_int_eq(0x2000, music.channel_1_tones[1]);
	mu_assert_int_eq(0x3000, music.channel_1_tones[2]);

	mu_assert_int_eq(15, music.channel_0_volume);
	mu_assert_int_eq(15, music.channel_1_volume);
}

MU_TEST(test_next_music_note) {
	unsigned int tone_idx = 0;
	unsigned int tone_limit = 32;
	char* music_notes = "C C#D D#E     F F#G    G#A A#B ";

	str_music_note note;

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("C", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("C#", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("D", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("D#", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("E", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("F", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("F#", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("G", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("G#", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("A", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("A#", note.str);

	note = next_music_note(music_notes, &tone_idx, &tone_limit);
	mu_assert_string_eq("B", note.str);
}


MU_TEST(test_create_simple_music_from_notes) {
	simple_music music;
	char channel_0_notes[] = "C C#D D#E F F#G G#A A#B "; // Octave 5
	char channel_1_notes[] = "C C#D D#E F F#G G#A A#B "; // Octave 4
	simple_music_create_from_notes(&music, channel_0_notes, channel_1_notes);

	unsigned int expected_channel_0_tones[] = {	0x0D6,	0x0CA,	0x0BE,	0x0B4,	0x0AA,	0x0A0,	0x097,	0x08F,	0x087,	0x07F,	0x078,	0x071 };// o5
	unsigned int expected_channel_1_tones[] = {	0x1AC,	0x194,	0x17D,	0x168,	0x153,	0x140,	0x12E,	0x11D,	0x10D,	0x0FE,	0x0F0,	0x0E3 };// o4

	mu_assert_int_eq(13, music.size);
	mu_assert_int_eq( 0, music.idx);

	for (unsigned int idx = 0; idx < 13; idx++) {
		mu_assert_int_eq(expected_channel_0_tones[idx], channel_0_notes[idx]);
		mu_assert_int_eq(expected_channel_1_tones[idx], channel_1_notes[idx]);
	}
}

MU_TEST(test_simple_music_play_tone) {
	simple_music music;
	unsigned int channel_0_tones[] = { 0x0000, 0x4000, 0x8000 };
	unsigned int channel_1_tones[] = { 0x1000, 0x2000, 0x3000 };
	unsigned int size = 3;

	simple_music_create(&music, channel_0_tones, channel_1_tones, size);

	channel_tones tones;

	tones = simple_music_play_tone(&music);
	mu_assert_int_eq(0x0000, tones.channel_0_tone);
	mu_assert_int_eq(0x1000, tones.channel_1_tone);
	mu_assert_int_eq(1, music.idx);

	tones = simple_music_play_tone(&music);
	mu_assert_int_eq(0x4000, tones.channel_0_tone);
	mu_assert_int_eq(0x2000, tones.channel_1_tone);
	mu_assert_int_eq(2, music.idx);

	tones = simple_music_play_tone(&music);
	mu_assert_int_eq(0x8000, tones.channel_0_tone);
	mu_assert_int_eq(0x3000, tones.channel_1_tone);
	mu_assert_int_eq(0, music.idx);	
}

unsigned int channel_0_volume;
unsigned int channel_1_volume;

void set_psg_volume(unsigned int channel, unsigned int volume) {
	if (channel == 0) {
		channel_0_volume = volume;
	}

	if (channel == 1) {
		channel_1_volume = volume;
	}
}

unsigned int get_psg_volume(unsigned int channel) {
	if (channel == 0) {
		return channel_0_volume;
	}

	if (channel == 1) {
		return channel_1_volume;
	}

	return 999;
}

MU_TEST(test_simple_music_test_volume) {
	simple_music music;
	unsigned int channel_0_tones[] = { 0x0000, 0x4000, 0x8000 };
	unsigned int channel_1_tones[] = { 0x1000, 0x2000, 0x3000 };
	unsigned int size = 3;

	simple_music_create(&music, channel_0_tones, channel_1_tones, size);

	simple_music_set_volume(&music, 10, 12, set_psg_volume);

	mu_assert_int_eq(10, get_psg_volume(0));
	mu_assert_int_eq(12, get_psg_volume(1));
}


MU_TEST(test_note_with_octave_to_tone) {
	unsigned int octaves = 8;
	char* notes[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

	unsigned int expected_tones[8][12] = {
	//	Octave	C		C#		D		D#		E		F		F#		G		G#		A		A#		B
			{	0xD5D,	0xC9C,	0xBE7,	0xB3C,	0xA9B,	0xA02,	0x973,	0x8EB,	0x86B,	0x7F2,	0x780,	0x714 },	// o1
			{	0x6AF,	0x64E,	0x5F4,	0x59E,	0x54E,	0x501,	0x4BA,	0x476,	0x436,	0x3F9,	0x3C0,	0x38A },	// o2
			{	0x357,	0x327,	0x2FA,	0x2CF,	0x2A7,	0x281,	0x25D,	0x23B,	0x21B,	0x1FD,	0x1E0,	0x1C5 },	// o3
			{	0x1AC,	0x194,	0x17D,	0x168,	0x153,	0x140,	0x12E,	0x11D,	0x10D,	0x0FE,	0x0F0,	0x0E3 },	// o4
			{	0x0D6,	0x0CA,	0x0BE,	0x0B4,	0x0AA,	0x0A0,	0x097,	0x08F,	0x087,	0x07F,	0x078,	0x071 },	// o5
			{	0x06B,	0x065,	0x05F,	0x05A,	0x055,	0x050,	0x04C,	0x047,	0x043,	0x040,	0x03C,	0x039 },	// o6
			{	0x035,	0x032,	0x030,	0x02D,	0x02A,	0x028,	0x026,	0x024,	0x022,	0x020,	0x01E,	0x01C },	// o7
			{	0x01B,	0x019,	0x018,	0x016,	0x015,	0x014,	0x013,	0x012,	0x011,	0x010,	0x00F,	0x00E }		// o8
		};

	for (unsigned int oct=1; oct <= octaves; oct++) {
		for(unsigned int idx=0; idx < 12; idx++) {
			unsigned int tone = simple_music_note_with_octave_to_tone(oct, notes[idx]);		
			mu_assert_int_eq(expected_tones[oct-1][idx], tone);
		}
	}
}

MU_TEST_SUITE(simple_music_test_suite) {
  	MU_RUN_TEST(test_create_simple_music);
  	MU_RUN_TEST(test_create_simple_music_from_notes);
  	MU_RUN_TEST(test_simple_music_play_tone);
  	MU_RUN_TEST(test_simple_music_test_volume);
  	MU_RUN_TEST(test_note_with_octave_to_tone);
}
