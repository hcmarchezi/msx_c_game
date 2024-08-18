#include "game_background.h"

#include "screen_1_tiling.h"

void game_background_define_tiles(game_background* stage, void (*vdp_vwrite)(void*, unsigned int, unsigned int)) {
	unsigned char ascii_start = 0x80;
	unsigned char pattern_count = stage->background_tiles_patterns_count;
	unsigned char* tile_patterns = stage->background_tiles_patterns;

	void screen_1_set_ascii_patterns(ascii_start, pattern_count, tile_patterns, vdp_vwrite);

	for (int ascii_group=0; ascii_group < 32; ascii_group++) {
		unsigned char foreground_background_color = stage->background_tiles_color[ascii_group];
		void screen_1_set_ascii_block_color_byte(
			ascii_group, 
			foreground_background_color, 
			vdp_vwrite);
	}
}

void game_background_display(game_background* stage, void (*vdp_vwrite)(void*, unsigned int, unsigned int)) {
	screen_1_fill_with_chars(stage->background_tiles_chars,vdp_vwrite); //32x24 chars
}
