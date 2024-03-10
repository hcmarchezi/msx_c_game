#include "minunit/minunit.h"
#include "screen_1_tiling.h"

#include "test_helper.h"

MU_TEST(test_set_tile_pattern) {
	unsigned int pattern_start = 16;
	unsigned int pattern_end   = 17;
	unsigned char tile_patterns[16] = { 
		 0x10i,  0x20i,  0x30i,  0x40i,  0x50i,  0x60i,  0x70i,  0x80i,
		0x110i, 0x120i, 0x130i, 0x140i, 0x150i, 0x160i, 0x170i, 0x180i };

	init_vpoke_func();

	screen_1_set_tile_patterns(pattern_start, pattern_end, tile_patterns, &vpoke_func);

	mu_assert_int_eq(16*8, vpoke_mem[0]);     mu_assert_int_eq(0x10i, vpoke_val[0]);
	mu_assert_int_eq(16*8 + 1, vpoke_mem[1]); mu_assert_int_eq(0x20i, vpoke_val[1]);
	mu_assert_int_eq(16*8 + 2, vpoke_mem[2]); mu_assert_int_eq(0x30i, vpoke_val[2]);
	mu_assert_int_eq(16*8 + 3, vpoke_mem[3]); mu_assert_int_eq(0x40i, vpoke_val[3]);
	mu_assert_int_eq(16*8 + 4, vpoke_mem[4]); mu_assert_int_eq(0x50i, vpoke_val[4]);
	mu_assert_int_eq(16*8 + 5, vpoke_mem[5]); mu_assert_int_eq(0x60i, vpoke_val[5]);
	mu_assert_int_eq(16*8 + 6, vpoke_mem[6]); mu_assert_int_eq(0x70i, vpoke_val[6]);
	mu_assert_int_eq(16*8 + 7, vpoke_mem[7]); mu_assert_int_eq(0x80i, vpoke_val[7]);

	mu_assert_int_eq(16*8 + 8, vpoke_mem[8]);   mu_assert_int_eq(0x110i, vpoke_val[8]);
	mu_assert_int_eq(16*8 + 9, vpoke_mem[9]);   mu_assert_int_eq(0x120i, vpoke_val[9]);
	mu_assert_int_eq(16*8 + 10, vpoke_mem[10]); mu_assert_int_eq(0x130i, vpoke_val[10]);
	mu_assert_int_eq(16*8 + 11, vpoke_mem[11]); mu_assert_int_eq(0x140i, vpoke_val[11]);
	mu_assert_int_eq(16*8 + 12, vpoke_mem[12]); mu_assert_int_eq(0x150i, vpoke_val[12]);
	mu_assert_int_eq(16*8 + 13, vpoke_mem[13]); mu_assert_int_eq(0x160i, vpoke_val[13]);
	mu_assert_int_eq(16*8 + 14, vpoke_mem[14]); mu_assert_int_eq(0x170i, vpoke_val[14]);
	mu_assert_int_eq(16*8 + 15, vpoke_mem[15]); mu_assert_int_eq(0x180i, vpoke_val[15]);
}

MU_TEST(test_set_tile_colors) {
	int pattern_group = 3;
	unsigned int foreground_color = 0xA;
	unsigned int background_color = 0x4;

	init_vpoke_func();

	screen_1_set_tile_colors(pattern_group, foreground_color, background_color, &vpoke_func);

	mu_assert_int_eq(8195, vpoke_mem[0]); 
	mu_assert_int_eq(164, vpoke_val[0]); // 164 = 0xA4 or 0xA(foreground) 0x4 (background)
}

void generate_sequential_array(int size, int* screen_data) {
	for (int index=0; index < size; index++) {
		screen_data[index] = index;
	}
}

void generate_memory_sequence(int start, int end, int* mem_arr) {
	for (int index=0; index <= end - start + 1; index++) {
		mem_arr[index] = index + start;
	}
}

MU_TEST(test_write_screen_tiles_int) {
	int screen_data[SCREEN_CHAR_SIZE];
	int mem_arr[SCREEN_CHAR_SIZE];
	generate_sequential_array(SCREEN_CHAR_SIZE, screen_data);
	generate_memory_sequence(6144, 6911, mem_arr);

	init_vpoke_func();
	screen_1_write_screen_tiles_int((int*)&screen_data, &vpoke_func);
	
	for (int index=0; index < 768; index++) {
		mu_assert_int_eq(index, vpoke_val[index]);
	}

	for (int index=0; index < 768; index++) {
	 	mu_assert_int_eq(index + 0x1800, vpoke_mem[index]);
	}
}

MU_TEST(test_write_screen_tiles_char) {
	const unsigned char tiles[] = {
		'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',
		'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',
		'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
		'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
		'0','1','2','3','4','5','6','7','8','9',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','0','1','2','3','4','5','6','7','8','9',
		'0','1','2','3','4','5','6','7','8','9',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','0','1','2','3','4','5','6','7','8','9',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',' ',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',' ',
		'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
		'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
		'!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!',
		'!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!','!',
		'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$',
		'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$',
		'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@',
		'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@',
		'<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<',
		'<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<','<',
		'>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>',
		'>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>','>',
		'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',
		'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=' };
	
	init_vpoke_func();
	screen_1_write_screen_tiles_char(tiles, &vpoke_func);

	char msg[64];
	for (int index=0; index < SCREEN_CHAR_SIZE; index++) {		
		sprintf(msg, ">> tiles[%i]=%c vpoke_val[%i]=%c\n", index, tiles[index], index, vpoke_val[index]);
		mu_assert(tiles[index] == vpoke_val[index], msg);
	}

	for (int index=0; index < SCREEN_CHAR_SIZE; index++) {
		mu_assert_int_eq(vpoke_mem[index], index+0x1800);
	}
}

MU_TEST_SUITE(screen_1_tiling_test_suite) {
  	MU_RUN_TEST(test_set_tile_pattern);
  	MU_RUN_TEST(test_set_tile_colors);
  	MU_RUN_TEST(test_write_screen_tiles_int);
  	MU_RUN_TEST(test_write_screen_tiles_char);
}