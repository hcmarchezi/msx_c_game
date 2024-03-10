#include "minunit/minunit.h"
#include "music_track.h"

#include<stdio.h>

music_track* music = 0;

music_note** channel_0_notes = 0;
music_note** channel_1_notes = 0; 


void test_music_track_setup(void) { 
	channel_0_notes = (music_note**)malloc(3 * sizeof(music_note*));
	channel_0_notes[0] = c_music_note(50, 8);
	channel_0_notes[1] = c_music_note(40, 8);
	channel_0_notes[2] = c_music_note(30, 4);

	channel_1_notes = (music_note**)malloc(4 * sizeof(music_note*));
	channel_1_notes[0] = c_music_note(90, 8);
	channel_1_notes[1] = c_music_note(70, 4);
	channel_1_notes[2] = c_music_note(60, 8);
	channel_1_notes[3] = c_music_note(80, 8);
}

void test_music_track_teardown(void) { 
	for (int i = 0; i < 3; i++) {
		free(channel_0_notes[i]);
	}

	for (int i = 0; i < 4; i++) {
		free(channel_1_notes[i]);
	}

	free(channel_0_notes);
	free(channel_1_notes);
}

MU_TEST(test_create_music_note) {
	music_note* note = c_music_note(50, 16);
	mu_check(note->tone == 50);
	mu_check(note->delay == 16);
	free(note);
}


MU_TEST(test_create_music_track) {		
	music = create_music_track(channel_0_notes, 3, channel_1_notes, 4);

	mu_check(music->channel_0_idx == 0);
	mu_check(music->channel_1_idx == 0);
	mu_check(music->channel_0_clock_counter == 0);
	mu_check(music->channel_1_clock_counter == 0);
	mu_check(music->channel_0_count == 3);
	mu_check(music->channel_1_count == 4);
	
	mu_check(music->channel_0[0]->tone == 50); mu_check(music->channel_0[0]->delay == 8);
	mu_check(music->channel_0[1]->tone == 40); mu_check(music->channel_0[1]->delay == 8);
	mu_check(music->channel_0[2]->tone == 30); mu_check(music->channel_0[2]->delay == 4);

	mu_check(music->channel_1[0]->tone == 90); mu_check(music->channel_1[0]->delay == 8);
	mu_check(music->channel_1[1]->tone == 70); mu_check(music->channel_1[1]->delay == 4);
	mu_check(music->channel_1[2]->tone == 60); mu_check(music->channel_1[2]->delay == 8);
	mu_check(music->channel_1[3]->tone == 80); mu_check(music->channel_1[3]->delay == 8);
}


MU_TEST(test_should_play_note) {
	mu_check(should_play_note_channel_0(music) == 1);
	mu_check(should_play_note_channel_1(music) == 1);
}


MU_TEST(test_play_next_note) {
	// music_note* note = 0;

	// note = play_next_note_channel_0(music);
	// mu_check(note->tone == 50); mu_check(note->delay == 8); mu_check(music->channel_0_clock_counter == 8);
	
	// note = play_next_note_channel_0(music);
	// mu_check(note->tone == 40); mu_check(note->delay == 8); mu_check(music->channel_0_clock_counter == 8);
	
	// note = play_next_note_channel_0(music);
	// mu_check(note->tone == 30); mu_check(note->delay == 4); mu_check(music->channel_0_clock_counter == 4);

	// note = play_next_note_channel_0(music);
	// mu_check(note->tone == 50); mu_check(note->delay == 8); mu_check(music->channel_0_clock_counter == 8);

	// note = play_next_note_channel_1(music);
	// mu_check(note->tone == 90); mu_check(note->delay == 8); mu_check(music->channel_1_clock_counter == 8);
	
	// note = play_next_note_channel_1(music);
	// mu_check(note->tone == 70); mu_check(note->delay == 4); mu_check(music->channel_1_clock_counter == 4);
	
	// note = play_next_note_channel_1(music);
	// mu_check(note->tone == 60); mu_check(note->delay == 8); mu_check(music->channel_1_clock_counter == 8);

	// note = play_next_note_channel_1(music);
	// mu_check(note->tone == 80); mu_check(note->delay == 8); mu_check(music->channel_1_clock_counter == 8);

	// note = play_next_note_channel_1(music);
	// mu_check(note->tone == 90); mu_check(note->delay == 8); mu_check(music->channel_1_clock_counter == 8);
}


MU_TEST(test_dec_channel_clock_counter) {
	// dec_channel_0_clock_counter(music);
	// mu_check(music->channel_0_clock_counter == 7);

	// dec_channel_0_clock_counter(music);
	// mu_check(music->channel_0_clock_counter == 6);

	// dec_channel_0_clock_counter(music);
	// mu_check(music->channel_0_clock_counter == 5);

	// dec_channel_1_clock_counter(music);
	// mu_check(music->channel_1_clock_counter == 7);

	// dec_channel_1_clock_counter(music);
	// mu_check(music->channel_1_clock_counter == 6);

	// dec_channel_1_clock_counter(music);
	// mu_check(music->channel_1_clock_counter == 5);
}

MU_TEST_SUITE(music_track_test_suite) {
  MU_SUITE_CONFIGURE(&test_music_track_setup, &test_music_track_teardown);
  MU_RUN_TEST(test_create_music_note);
  MU_RUN_TEST(test_create_music_track);
  MU_RUN_TEST(test_should_play_note);
  MU_RUN_TEST(test_play_next_note);
  MU_RUN_TEST(test_dec_channel_clock_counter);
}