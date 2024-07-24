#include<msx/gfx.h>
#include<video/tms99x8.h>
#include<psg.h>


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "data/sprites.h"
#include "data/tiles.h"
#include "data/game_title.h"

#include "msxgame/game_sprite.h"
#include "msxgame/music_tones.h"
#include "msxgame/screen_1_tiling.h"
#include "msxgame/msx_psg_helper.h"
#include "msxgame/game_sprite_collision.h"
#include "msxgame/ship_sequence.h"

#include "game/ship_sequence.h"


game_sprite player;
game_sprite player_shoot;

char channel_0_notes[] = "DFAFDFAFDFAFDFAFCFAFCFAFCFAFCFAF";
char channel_1_notes[] = "AAAAAAFDAAAAAAFACCCCCCFFCCCCCCFF";
unsigned int note_count = 32;

unsigned int channel_0_tones[32];
unsigned int channel_1_tones[32];

void game_ship_movement_init() {
  build_seq_func_1(&move_sequence_1, 128);
  build_seq_func_2(&move_sequence_2, 128);
  build_seq_func_3(&move_sequence_3, 128);
  build_seq_func_zero(&move_sequence_zero, 128);
}

void initialize_psg_channels() {
	set_psg(8, 16);
	set_psg(9, 16);
	set_psg(11, 0x88);
	set_psg(12, 0x13);
	set_psg(13, 0);
}

///////////////////////////////////// main program ///////////

void main() {
  vdp_color(15, 1, 5);
    vdp_set_mode(mode_1);
    vdp_set_sprite_mode(sprite_large);

    ///////////////// SPRITE PATTERN DEFINITIONS /////////////

    vdp_set_sprite_16(0, player_pattern);
    vdp_set_sprite_16(1, enemy_pattern);
    vdp_set_sprite_16(2, player_shoot_pattern);

    vdp_set_sprite_16(3, enemy_pattern_2);
    vdp_set_sprite_16(4, enemy_pattern_3);
    vdp_set_sprite_16(5, star_ship);
    
    vdp_set_sprite_16(10, explosion_1_pattern);
    vdp_set_sprite_16(11, explosion_2_pattern);
    vdp_set_sprite_16(12, explosion_3_pattern);
    vdp_set_sprite_16(13, explosion_4_pattern);

    ////////////////// ASCII PATTERN DEFINITIONS //////////////

    screen_1_set_ascii_patterns(0x10, 4, planet_pattern, vdp_vwrite);
    screen_1_set_ascii_patterns(0x14, 4, moon_pattern, vdp_vwrite);
    screen_1_set_ascii_patterns(0x18, 4, stars_pattern, vdp_vwrite);

    screen_1_set_ascii_patterns(0x80, 64, game_title_tile_patterns, vdp_vwrite);

    ////////////////// ASCII PATTERN COLORS ///////////////////

    screen_1_set_ascii_block_color(2,  4, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(3,  15, 1, vdp_vwrite);

    screen_1_set_ascii_block_color(16, 4, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(17, 4, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(18, 5, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(19, 5, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(20, 7, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(21, 7, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(22, 15, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(23, 15, 1, vdp_vwrite);

    ////////////////// WRITE GAME TITLE TILES /////////////////

    screen_1_fill_with_chars(game_title_chars, vdp_vwrite);
    while (!get_trigger(0));

    ////////////////// WRITE SCREEN 1 TILES ///////////////////

    screen_1_fill_with_chars(screen_1_tiles_with_stars_and_planet, vdp_vwrite); 
    

    /////////////////// SETUP ENEMY SHIP SEQUENCE /////////////   

    game_ship_movement_init();

    ship_sequence sequences[2];
    new_ship_sequence_1(&sequences[0]);
    new_ship_sequence_2(&sequences[1]);
    new_ship_sequence_3(&sequences[2]);
    new_ship_sequence_4(&sequences[3]);
    unsigned char sequence_idx = 0;
    unsigned char sequence_count = 4;

    ///////////////////////////////////////////////////////////

    int player_score = 0;
    screen_1_init_score(vdp_vwrite);
    screen_1_print_score(player_score, vdp_vwrite);

    init_game_sprite(&player, 0, 128, 170, 15, 0, 1, explosion_patterns, explosion_pattern_count);
    init_game_sprite(&player_shoot, 2, -20, -20, 6, 2, 1, explosion_patterns, explosion_pattern_count);

    music_tones tones;
    map_notes_to_tones(3, channel_0_notes, note_count, channel_0_tones);
	  map_notes_to_tones(4, channel_1_notes, note_count, channel_1_tones);
	  create_music_tones(&tones, channel_0_tones, channel_1_tones, note_count);

    clock_t start_t = clock();
    clock_t end_t = clock();

    for (;;) {
    	
	    int stick = get_stick(0);
    	game_sprite_move(&player, stick); 
    	game_sprite_display(&player, vdp_put_sprite_16);
    	game_sprite_display(&player_shoot, vdp_put_sprite_16);


      ship_sequence_run(sequences[sequence_idx], vdp_put_sprite_16);


    	if (get_trigger(0) && player_shoot.y == -20) {
    		set_psg(10, 15);
    		player_shoot.y = player.y - 16;
    		player_shoot.x = player.x;
    	}    	

    	player_shoot.y -= 5;

    	if (player_shoot.y < -20) {
    		set_psg(10, 0);
    		player_shoot.y = -20;
    	} else {
    		set_psg(4, player_shoot.y + 51);
    		set_psg(5, 1);
    	}

    	game_sprite_display(&player_shoot, vdp_put_sprite_16);

    	if ((long)(end_t - start_t) > 10) {
    		initialize_psg_channels();
    		music_tones_play_tone(&tones, 0, &set_psg);
    		music_tones_play_tone(&tones, 1, &set_psg);
    	 	music_tones_next_tone(&tones);
    	 	start_t = clock();
    	 	end_t = clock();
    	} else {
    		end_t = clock();
    	}

      unsigned char result = ship_sequence_collision(&player_shoot, &sequences[sequence_idx], vdp_put_sprite_16);
      if (result == 'Y') {
        player_score += 10;
        screen_1_print_score(player_score, vdp_vwrite);
      }
      int end_of_sequence = sequences[sequence_idx].end_of_sequence;
      if ((sequence_idx < sequence_count - 1)&&(end_of_sequence == 1)) {
        sequence_idx++;
      }

    }
}
