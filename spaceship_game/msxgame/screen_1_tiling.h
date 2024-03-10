#ifndef SCREEN_1_TILING_H
#define SCREEN_1_TILING_H

void screen_1_set_tile_patterns(unsigned int pattern_start, unsigned int pattern_end, unsigned char* tile_patterns, int (*vpoke)(int, int));

void screen_1_set_tile_colors(int pattern_group, unsigned int foreground_color, unsigned int background_color, int (*vpoke)(int, int));

void screen_1_write_screen_tiles_int(const int* ascii, int (*vpoke)(int, int)); // 32x24 ascii code characters

void screen_1_write_screen_tiles_char(const unsigned char* tiles, int (*vpoke)(int, int)); // 32x24 characters

#endif
