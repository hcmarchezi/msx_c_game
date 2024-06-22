#include "screen_1_tiling.h"

void screen_1_fill_with_chars( //32x24 chars
	const unsigned char* chars, 
	void (*vdp_vwrite)(void*, unsigned int, unsigned int)) {
		vdp_vwrite((void*)chars, 0x1800, 764); // 32x24 = 768
} 

void screen_1_set_ascii_patterns(
	unsigned char ascii_start, unsigned char ascii_count, const unsigned char* patterns, 
	void (*vdp_vwrite)(void*, unsigned int, unsigned int)) {
    	unsigned int mem_start = (unsigned int)ascii_start * 8;
    	unsigned int mem_count = (unsigned int)ascii_count * 8;
    	vdp_vwrite((void*)patterns, mem_start, mem_count);
}

void screen_1_set_ascii_block_color(
	unsigned char ascii_group, unsigned char foreground_color, unsigned char background_color,
	void (*vdp_vwrite)(void*, unsigned int, unsigned int)) {
    	unsigned int mem_start = 0x2000 + ascii_group;
    	unsigned char color = foreground_color * 16 + background_color;
    	vdp_vwrite((void*)&color, mem_start, 1);
}















