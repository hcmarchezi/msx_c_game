#ifndef MUSIC_TONES_H
#define MUSIC_TONES_H

typedef struct {
	unsigned int* channel_0_tones;
	unsigned int* channel_1_tones;
	unsigned int count;
	unsigned int index;
} music_tones;

void create_music_tones(music_tones* tones, unsigned int* channel_0_tones, unsigned int* channel_1_tones, unsigned int count);

void music_tones_play_tone(music_tones* tones, unsigned int channel, void (*set_psg)(unsigned int, unsigned int));

void music_tones_next_tone(music_tones* tones);

#endif
