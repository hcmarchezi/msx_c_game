#include<msx/gfx.h>
#include<video/tms99x8.h>
#include<psg.h>


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "data/sprites.h"
#include "data/tile_patterns.h"
#include "data/game_title.h"

#include "msxgame/game_sprite.h"
#include "msxgame/screen_1_tiling.h"
#include "msxgame/msx_psg_helper.h"
#include "msxgame/game_sprite_collision.h"
#include "msxgame/ship_sequence.h"
#include "msxgame/game_background.h"

#include "game/ship_sequence.h"
#include "game/ship_music_track.h"
#include "game/ship_stage.h"

game_sprite player;
game_sprite player_shoot;



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

void wait_for(clock_t interval) {
  clock_t start_int = clock();
  clock_t end_int = clock();
  while ((end_int - start_int) < interval) {
    end_int = clock();
  }
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
    screen_1_set_ascii_patterns(0x1C, 4, commet_pattern, vdp_vwrite);

    // 0x20 - 0x5F -> visible characters - not to be replaced (unless by better fonts)

    screen_1_set_ascii_patterns(0x60, 16, spaceship_pattern, vdp_vwrite); // 16 bytes
    screen_1_set_ascii_patterns(0x70, 16, asteroid_pattern, vdp_vwrite); // 16 bytes
    screen_1_set_ascii_patterns(0x80, 64, game_title_tile_patterns, vdp_vwrite); // 64 bytes - 0x80 - 0xBF

    // screen_1_set_ascii_patterns(0xC0, ..., ....); // 16 bytes
    // screen_1_set_ascii_patterns(0xD0, ..., ....); // 16 bytes
    // screen_1_set_ascii_patterns(0xE0, ..., ....); // 16 bytes
    // screen_1_set_ascii_patterns(0xF0, ..., ....); // 16 bytes

    ////////////////// ASCII PATTERN COLORS ///////////////////

    screen_1_set_ascii_block_color(2,  4, 1, vdp_vwrite);  // planet / moon pattern
    screen_1_set_ascii_block_color(3,  15, 1, vdp_vwrite); // stars / comment pattern

    screen_1_set_ascii_block_color(14,  9, 1, vdp_vwrite); // asteroid part 1
    screen_1_set_ascii_block_color(15,  9, 1, vdp_vwrite); // asteroid part 2

    screen_1_set_ascii_block_color(16, 4, 1, vdp_vwrite);  ////////////////////
    screen_1_set_ascii_block_color(17, 4, 1, vdp_vwrite);  //  
    screen_1_set_ascii_block_color(18, 5, 1, vdp_vwrite);  // 
    screen_1_set_ascii_block_color(19, 5, 1, vdp_vwrite);  // game
    screen_1_set_ascii_block_color(20, 7, 1, vdp_vwrite);  // title
    screen_1_set_ascii_block_color(21, 7, 1, vdp_vwrite);  // pattern
    screen_1_set_ascii_block_color(22, 15, 1, vdp_vwrite); //
    screen_1_set_ascii_block_color(23, 15, 1, vdp_vwrite); ///////////////////

    ////////////////// GAME SEQUENCE /////////////////////////////////////////

    game_stage stages[3];
    create_ship_stage_1(stages[0]);
    create_ship_stage_2(stages[1]);
    create_ship_stage_3(stages[2]);

    unsigned char sequence_idx = 0;
    unsigned char sequence_count = 3;

    ////////////////// WRITE GAME TITLE TILES /////////////////

    screen_1_fill_with_chars(game_title_chars, vdp_vwrite);
    while (!get_trigger(0));

    ////////////////// SETUP SHIP MOVEMENT ////////////////////

    game_ship_movement_init();

    /////////////////// SETUP GAME VARS ///////////////////////

    int player_score = 0;
    screen_1_init_score(vdp_vwrite);
    screen_1_print_score(player_score, vdp_vwrite);

    init_game_sprite(&player, 0, 128, 170, 15, 0, 1, explosion_patterns, explosion_pattern_count);
    init_game_sprite(&player_shoot, 2, -20, -20, 6, 2, 1, explosion_patterns, explosion_pattern_count);

    unsigned char explosion_sound_tones[] = { 0x60, 0x40, 0x20, 0x10, 0x20, 0x40, 0x60 };

    //////////////////////// STAGE LOOP /////////////////////////////
    while(sequence_idx < sequence_count) {

      screen_1_clear(vdp_vwrite);
      screen_1_printf(
        stages[sequence_idx].stage_name, 
        stages[sequence_idx].stage_name_count, 
        5, 10, 
        vdp_vwrite);
      wait_for(120);

      ////////////////// WRITE SCREEN 1 TILES ///////////////////
      screen_1_fill_with_chars(stages[sequence_idx].background, vdp_vwrite); 

      ///////////////////////////////////////////////////////////

      clock_t start_t = clock();
      clock_t end_t = clock();

      for (;;) {
      	
  	    int stick = get_stick(0);
      	game_sprite_move(&player, stick); 
      	game_sprite_display(&player, vdp_put_sprite_16);
      	game_sprite_display(&player_shoot, vdp_put_sprite_16);

        ship_sequence_run(stages[sequence_idx].sequence, vdp_put_sprite_16); 


        ////////////////////////////////////////////////////////////////////////////

        int any_explosion = 0;
        for (int index=0; index < stages[sequence_idx].sequence.ship_count; index++) {
          if (stages[sequence_idx].sequence.ships[index]->status == 'E') {
            set_psg(10, 15);
            unsigned char explosion_idx = stages[sequence_idx].sequence.ships[index]->explosion_idx;
            set_psg(4, explosion_sound_tones[ explosion_idx ]);
            set_psg(5, 0x1);
            any_explosion = 1;
          }
        }

        ////////////////////////////////////////////////////////////////////////////


      	if (get_trigger(0) && player_shoot.y == -20) {
      		set_psg(10, 15);
      		player_shoot.y = player.y - 16;
      		player_shoot.x = player.x;
      	}    	

      	player_shoot.y -= 5;


        if ((player_shoot.y < -20)&&(any_explosion == 0)) { 
          set_psg(10, 0);
        }


      	if (player_shoot.y < -20) {
      		player_shoot.y = -20;
      	} else {
      		set_psg(4, player_shoot.y + 51);
      		set_psg(5, 1);
      	}

      	game_sprite_display(&player_shoot, vdp_put_sprite_16);

      	if ((long)(end_t - start_t) > 10) {
      		initialize_psg_channels();
      		music_tones_play_tone(&stages[sequence_idx].sound_track, 0, &set_psg); //tones
      		music_tones_play_tone(&stages[sequence_idx].sound_track, 1, &set_psg); //tones
      	 	music_tones_next_tone(&stages[sequence_idx].sound_track); //tones
      	 	start_t = clock();
      	 	end_t = clock();
      	} else {
      		end_t = clock();
      	}

        /////////////////////////////////////////////////
        unsigned char result = ship_sequence_collision(&player_shoot, &stages[sequence_idx].sequence, vdp_put_sprite_16);
        if (result == 'Y') {
          player_score += 10;
          screen_1_print_score(player_score, vdp_vwrite);
        }

        ///////////////////////////////////////////////////////////
        int end_of_sequence = stages[sequence_idx].sequence.end_of_sequence;
        if (end_of_sequence == 1) {
          break;
        }

      }

      // inc sequence idx
      if (sequence_idx < sequence_count - 1) {
        sequence_idx++;
      } else {
        break;
      }
    }

    ////////////////////////////////////////////////////////////
    // end of game
    ////////////////////////////////////////////////////////////
    wait_for(60);
    screen_1_clear(vdp_vwrite);
    unsigned char* end_game_msg = "CONGRATULATIONS End of game";
    unsigned int end_game_msg_length = 27;
    screen_1_printf(end_game_msg, end_game_msg_length, 5, 15, vdp_vwrite);
    wait_for(120);
}
