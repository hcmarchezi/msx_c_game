#include "simple_music.h"

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

void simple_music_create(simple_music* music, unsigned int* channel_0_tones, unsigned int* channel_1_tones, unsigned int size) {
	music->size = size;
	music->idx = 0;
	music->channel_0_tones = channel_0_tones;
	music->channel_1_tones = channel_1_tones;
	music->channel_0_volume = 15;
	music->channel_1_volume = 15;
}

void simple_music_create_empty(simple_music* music, unsigned int size) {
	music->size = size;
	music->idx = 0;

	music->channel_0_tones = (unsigned int *)malloc(sizeof(unsigned int)*size);
	music->channel_1_tones = (unsigned int *)malloc(sizeof(unsigned int)*size);

	music->channel_0_volume = 15;
	music->channel_1_volume = 15;	
}

str_music_note create_music_note() {
	str_music_note note;
	note.str[0] = 0;
	note.str[1] = 0;
	note.str[2] = 0;
	return note;
}

str_music_note next_music_note(char* channel_notes, unsigned int* tone_idx, unsigned int* tone_limit) {
	str_music_note note = create_music_note();
	unsigned int v_tone_idx = *tone_idx;
	unsigned int v_tone_limit = *tone_limit;
	printf("-----------------------------------------\n");
	printf("next_music_note: tone_idx=%i tone_limit=%i", v_tone_idx, v_tone_limit);

	while ((channel_notes[v_tone_idx] == ' ') && (v_tone_idx < v_tone_limit)) {
		printf("-----------------------------------------\n");
		printf("next_music_note: tone_idx=%i tone_limit=%i", v_tone_idx, v_tone_limit);
		v_tone_idx++;
	}

	if (v_tone_idx == v_tone_limit) {
		*tone_idx = v_tone_idx;
		*tone_limit = v_tone_limit;
		return note;
	}

	note.str[0] = channel_notes[v_tone_idx];	
	
	v_tone_idx++;
	if (v_tone_idx < v_tone_limit) {
		if (channel_notes[v_tone_idx] == '#') {
			note.str[1] = '#';
			v_tone_idx++;
		}
	}

	*tone_idx = v_tone_idx;
	*tone_limit = v_tone_limit;
	return note;
}


unsigned int music_note_to_idx(char* note) {
	printf("--------------> music_note_to_idx: note=%s\n", note);
	
	unsigned int result;
	     if (note[0] == 'C' && note[1] != '#') { result = 0; }
	else if (note[0] == 'C' && note[1] == '#') { result = 1; }
	else if (note[0] == 'D' && note[1] != '#') { result = 2; }
	else if (note[0] == 'D' && note[1] == '#') { result = 3; }
	else if (note[0] == 'E' && note[1] != '#') { result = 4; }
	else if (note[0] == 'F' && note[1] != '#') { result = 5; }
	else if (note[0] == 'F' && note[1] == '#') { result = 6; }
	else if (note[0] == 'G' && note[1] != '#') { result = 7; }
	else if (note[0] == 'G' && note[1] == '#') { result = 8; }
	else if (note[0] == 'A' && note[1] != '#') { result = 9; }
	else if (note[0] == 'A' && note[1] == '#') { result = 10; }
	else if (note[0] == 'B' && note[1] != '#') { result = 11; }
	else { result = 65535; }

	printf("--------------> music_note_to_idx: result=%i\n", result);

	return result;
}

unsigned int simple_music_note_with_octave_to_tone(unsigned int octave, char* note) {
	static unsigned int tones[8][12] = {
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


	printf("simple_music_note_with_octave_to_tone: octave=%i note=%s\n", octave, note);
	unsigned int i = octave - 1;
	unsigned int j = music_note_to_idx(note);
	printf("simple_music_note_with_octave_to_tone: i=%i j=%i\n", i, j);

	return tones[i][j];
}

void simple_music_create_from_notes(simple_music* music, char* channel_0_notes, char* channel_1_notes) {
	unsigned int tone_limit = 128;
	unsigned int tone_idx;
	unsigned int music_note_idx;

	printf("\nchannel_0_notes=%s\n", channel_0_notes);
	printf("\nchannel_1_notes=%s\n", channel_1_notes);

	music_note_idx = 0;
	tone_idx = 0;
	while (1) { // return 0 when finished
		printf("\nmusic_note_idx=%i tone_limit=%i", music_note_idx, tone_limit);
		printf("--------------------------------------------\n");
		str_music_note note = next_music_note(channel_0_notes, &music_note_idx, &tone_limit);
		if (note.str[0]==0) break;

		unsigned int tone = simple_music_note_with_octave_to_tone(5, note.str);
		music->channel_0_tones[tone_idx] = tone;
		tone_idx++;
	}

	music_note_idx = 0;
	tone_idx = 0;
	while (1) { // return 0 when finished
		printf("\nmusic_note_idx=%i tone_limit=%i", music_note_idx, tone_limit);
		printf("--------------------------------------------\n");
		str_music_note note = next_music_note(channel_1_notes, &music_note_idx, &tone_limit);
		if (note.str[0]==0) break;

		unsigned int tone = simple_music_note_with_octave_to_tone(4, note.str);
		music->channel_1_tones[tone_idx] = tone;
		tone_idx++;
	}

	music->channel_0_tones = 0;
}

channel_tones simple_music_play_tone(simple_music* music) {
	channel_tones tones;
	tones.channel_0_tone = music->channel_0_tones[music->idx];
	tones.channel_1_tone = music->channel_1_tones[music->idx];
	music->idx += 1;
	if (music->idx >= music->size) {
		music->idx = 0;
	}
	return tones;
}

int simple_music_should_play_next_tone(simple_music* music) {
	return 0;
}

void simple_music_set_volume(simple_music* music, unsigned int channel_0_volume, unsigned int channel_1_volume, void (* psg_volume)(unsigned int, unsigned int)) {
	psg_volume(0, channel_0_volume);
	psg_volume(1, channel_1_volume);
}


