#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include "music_tones.h"
#include "ship_sequence.h"

typedef struct {
	unsigned char* stage_name;
	unsigned int stage_name_count;
	music_tones sound_track;
	ship_sequence sequence;
	unsigned char* background;
} game_stage;

#endif