#include "ship_stage.h"

#include "ship_sequence.h"
#include "../data/tile_backgrounds.h"
#include "ship_music_track.h"

unsigned char* stage_1_name = "STAGE 1 THE BEGININGS";
void create_ship_stage_1(game_stage* stage) {
	stage->stage_name = stage_1_name;
	stage->stage_name_count = 21;
	new_ship_sequence_1(&stage->sequence);
	stage->background = stage_1_char_tiles;
	create_music_track_1(&stage->sound_track);
}

unsigned char* stage_2_name = "STAGE 2 BATTLESHIP";
void create_ship_stage_2(game_stage* stage) {
	stage->stage_name = stage_2_name;
	stage->stage_name_count = 18;
	new_ship_sequence_2(&stage->sequence);
	stage->background = stage_2_char_tiles;
	create_music_track_2(&stage->sound_track);
}

unsigned char* stage_3_name = "STAGE 3 ASTEROIDS";
void create_ship_stage_3(game_stage* stage) {
	stage->stage_name = stage_3_name;
	stage->stage_name_count = 17;
	new_ship_sequence_3(&stage->sequence);
	stage->background = stage_3_char_tiles;
	create_music_track_3(&stage->sound_track);
}