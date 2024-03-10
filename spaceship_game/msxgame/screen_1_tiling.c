#include "screen_1_tiling.h"


void screen_1_set_tile_patterns(unsigned int pattern_start, unsigned int pattern_end, unsigned char* tile_patterns, int (*vpoke)(int, int)) {
	int tile_idx = 0;
	for (int mem = pattern_start * 8; mem < (pattern_end+1) * 8; mem++) {
		vpoke(mem, tile_patterns[tile_idx]);
		tile_idx++;
	}	
}

void screen_1_set_tile_colors(int pattern_group, unsigned int foreground_color, unsigned int background_color, int (*vpoke)(int, int)) {
	int mem = 8192 + pattern_group;
	int color = (int)foreground_color * 16 + (int)background_color;
	vpoke(mem, color);
}

void screen_1_write_screen_tiles_int(const int* ascii, int (*vpoke)(int, int)) { // 32x24 ascii code characters
	int ascii_index = 0;
	for (int mem = 0x1800; mem <=0x1AFF; mem++) {
		vpoke(mem, ascii[ascii_index]);
		ascii_index++;
	}
}

void screen_1_write_screen_tiles_char(const unsigned char* tiles, int (*vpoke)(int, int)) { // 32x24 characters
	int tile_idx = 0;
	for (int mem = 0x1800; mem <=0x1AFF; mem++) {
		vpoke(mem, (int)tiles[tile_idx]);
		tile_idx++;
	}
}

