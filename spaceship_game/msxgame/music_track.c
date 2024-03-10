#include "music_track.h"

#include<stdlib.h>
#include<stdio.h>

music_note* c_music_note(int tone, int delay) {
	music_note* note = (music_note*)malloc(sizeof(music_note));
	note->tone = tone;
	note->delay = delay;
	return note;
}

music_track* create_music_track(
	music_note** channel_0_notes, int channel_0_count, 
	music_note** channel_1_notes, int channel_1_count){
	
	music_track* music = (music_track*)malloc(sizeof(music_track));

	music->channel_0 = channel_0_notes;
	music->channel_1 = channel_1_notes;
	music->channel_0_count = channel_0_count;
	music->channel_1_count = channel_1_count;
	music->channel_0_idx = 0;
	music->channel_1_idx = 0;
	music->channel_0_clock_counter = 0;
	music->channel_1_clock_counter = 0;

	return music;
}

char should_play_note_channel_0(music_track* music) {
	return music->channel_0_clock_counter == 0;
}

char should_play_note_channel_1(music_track* music) {
	return music->channel_1_clock_counter == 0;
}

music_note* play_next_note_channel_0(music_track* music) {
	music_note* note = music->channel_0[music->channel_0_idx++];
	music->channel_0_clock_counter = note->delay;
	if (music->channel_0_idx >= music->channel_0_count) {
		music->channel_0_idx = 0;
	}
	return note;
}

music_note* play_next_note_channel_1(music_track* music) {
	music_note* note = music->channel_1[music->channel_1_idx++];
	music->channel_1_clock_counter = note->delay;
	if (music->channel_1_idx >= music->channel_1_count) {
		music->channel_1_idx = 0;
	}
	return note;
}

void dec_channel_0_clock_counter(music_track* music) {
	music->channel_0_clock_counter--;
}

void dec_channel_1_clock_counter(music_track* music) {
	music->channel_1_clock_counter--;
}

