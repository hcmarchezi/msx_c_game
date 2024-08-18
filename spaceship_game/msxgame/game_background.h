#ifndef GAME_BACKGROUND_H
#define GAME_BACKGROUND_H

typedef struct {
	unsigned char background_tiles_patterns_count; // number of ASCII symbols to be redefined (1 ASCII symbol = 8 bytes)

	unsigned char* background_tiles_patterns;	// screen 1 ASCII symbol patterns
												// define ASCII symbol patterns to be used in background 
												// array starts with ASCII symbol 0x80 until symbol 0xff (128 char limit)

	unsigned char* background_tiles_chars;		// screen 1 background chars => 32x24 chars => limit of 768 chars

	unsigned char background_tiles_color[32];	// screen 1 char block color => 1 block => front/background color for evey 8 chars
												// * color format => 1 byte => 00-FF
												//		* first hex digit is font color
												//		* second hex digit is background color
												//
												// every array position defines the following char ranges:
												// 00-07: 
												// 08-0F: 
												// 10-17: 
												// 18-1F: 
												// 20-27: 
												// 28-2F: 
												// 30-37: 
												// 38-3F: 
												// 40-47: 
												// 48-4F: 
												// 50-57: 
												// 58-5F: 
												// 60-67: 
												// 68-6F: 
												// 70-77: 
												// 78-7F: 
												// 80-87: background tile patterns
												// 88-8F: 
												// 90-97: 
												// 98-9F: 
												// A0-A7: 
												// A8-AF: 
												// B0-B7: 
												// B8-BF: 
												// C0-C7: 
												// C8-CF: 
												// D0-D7: 
												// D8-DF: 
												// E0-E7: 
												// E8-EF: 
												// F0-F7: 
												// F8-FF: 
} game_background;

void game_background_define_tiles(game_background* stage, void (*vdp_vwrite)(void*, unsigned int, unsigned int));

void game_background_display(game_background* stage, void (*vdp_vwrite)(void*, unsigned int, unsigned int));

#endif