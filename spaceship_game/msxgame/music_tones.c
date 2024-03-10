#include "music_tones.h"

void create_music_tones(music_tones* tones, unsigned int* channel_0_tones, unsigned int* channel_1_tones, unsigned int count) {
	tones->channel_0_tones = channel_0_tones;
	tones->channel_1_tones = channel_1_tones;
	tones->count = count;
	tones->index = 0;
}

void music_tones_play_tone(music_tones* tones, unsigned int channel, void (*set_psg)(unsigned int, unsigned int)) {
	unsigned int tone;
	unsigned int reg_tone_h;
	unsigned int reg_tone_l;
	if (channel == 0) {
		tone = tones->channel_0_tones[tones->index];
		reg_tone_h = 1;
		reg_tone_l = 0;
	} else if (channel == 1) {
		tone = tones->channel_1_tones[tones->index];
		reg_tone_h = 3;
		reg_tone_l = 2;
	} else {		
		return;
	}

	unsigned int h_tone = tone/256;
	unsigned int l_tone = tone%256;

	set_psg(reg_tone_l, l_tone);
	set_psg(reg_tone_h, h_tone);
}

void music_tones_next_tone(music_tones* tones) {
	tones->index++;
	if (tones->index >= tones->count) {
		tones->index = 0;
	}
}