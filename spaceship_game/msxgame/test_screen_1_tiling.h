#include "minunit/minunit.h"
#include "screen_1_tiling.h"

#include "test_helper.h"

MU_TEST(test_screen_1_set_ascii_patterns) {
	init_vpoke_vwrite_func();
	
	unsigned char ascii_start = 0x50;
	unsigned char ascii_count = 0x10;
	unsigned char* patterns = 0x1000;
	
	screen_1_set_ascii_patterns(
		ascii_start, ascii_count, patterns, 
		vpoke_vwrite_func);
		
	mu_assert(vpoke_vwrite_mem_start, 0x50);
	mu_assert(vpoke_vwrite_mem_count, 0x10);
	mu_assert(vpoke_vwrite_data, 0x1000);
}

MU_TEST(test_screen_1_set_ascii_block_color) {
	init_vpoke_vwrite_func();

	unsigned char ascii_group = 0x03;
	unsigned char foreground_color = 0x02;
	unsigned char background_color = 0x05;

	screen_1_set_ascii_block_color(
		ascii_group, foreground_color, background_color,
		vpoke_vwrite_func);
		
	mu_assert(vpoke_vwrite_mem_start, 0x2003);
	mu_assert(vpoke_vwrite_mem_count, 1);
}

MU_TEST(test_screen_1_fill_with_chars) {
	init_vpoke_vwrite_func();
	unsigned char* pattern_chars = 0x1500;

	screen_1_fill_with_chars(
		pattern_chars, 
		vpoke_vwrite_func);
			
	mu_assert(vpoke_vwrite_mem_start, 0x1800);
	mu_assert(vpoke_vwrite_mem_count, 768);
	mu_assert(vpoke_vwrite_data, 0x1500);
}



MU_TEST_SUITE(screen_1_tiling_test_suite) {  	
  	MU_RUN_TEST(test_screen_1_set_ascii_patterns);
  	MU_RUN_TEST(test_screen_1_set_ascii_block_color);
  	MU_RUN_TEST(test_screen_1_fill_with_chars);
  	
}
