#ifndef SIMPLE_MUSIC_H
#define SIMPLE_MUSIC_H

#include<time.h>

typedef struct {
	unsigned int* channel_0_tones;
	unsigned int* channel_1_tones;
	unsigned int size;
	unsigned int idx;
	clock_t counter;
	unsigned int channel_0_volume;
	unsigned int channel_1_volume;
} simple_music;

typedef struct {
	unsigned int channel_0_tone;
	unsigned int channel_1_tone;
} channel_tones;

typedef struct {
	char str[3];
} str_music_note;


void simple_music_create(simple_music* music, unsigned int* channel_0_tones, unsigned int* channel_1_tones, unsigned int size);

void simple_music_create_empty(simple_music* music, unsigned int tone_size);

str_music_note next_music_note(char* channel_notes, unsigned int* tone_idx, unsigned int* tone_limit);

unsigned int simple_music_note_with_octave_to_tone(unsigned int octave, char* note);

// params:
// * music: simple_music* - ref to simple music object
// * channel_0_notes: char* - null-terminated string with music notes for octave 5
// * channel_1_notes: char* - null-terminated string with music notes for octave 4
void simple_music_create_from_notes(simple_music* music, char* channel_0_notes, char* channel_1_notes);

channel_tones simple_music_play_tone(simple_music* music);

int simple_music_should_play_next_tone(simple_music* music);

void simple_music_set_volume(simple_music* music, unsigned int channel_0_volume, unsigned int channel_1_volume, void (* psg_volume)(unsigned int, unsigned int));

#endif
