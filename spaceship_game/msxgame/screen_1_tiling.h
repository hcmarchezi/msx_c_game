#ifndef SCREEN_1_TILING_H
#define SCREEN_1_TILING_H

void screen_1_fill_with_chars(
	const unsigned char* chars, 
	void (*vdp_vwrite)(void*, unsigned int, unsigned int)); //32x24 chars

void screen_1_set_ascii_patterns(
	unsigned char ascii_start, unsigned char ascii_count, const unsigned char* patterns, 
	void (*vdp_vwrite)(void*, unsigned int, unsigned int));

void screen_1_set_ascii_block_color(
	unsigned char ascii_group, unsigned char foreground_color, unsigned char background_color,
	void (*vdp_vwrite)(void*, unsigned int, unsigned int));
  
#endif
