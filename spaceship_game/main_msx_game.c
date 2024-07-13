#include<msx/gfx.h>
#include<video/tms99x8.h>
#include<psg.h>


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "data/sprites.h"
#include "data/tiles.h"
#include "msxgame/game_sprite.h"
#include "msxgame/music_tones.h"
#include "msxgame/screen_1_tiling.h"
#include "msxgame/msx_psg_helper.h"
#include "msxgame/game_sprite_collision.h"
#include "msxgame/ship_sequence.h"


game_sprite player;
game_sprite player_shoot;

char channel_0_notes[] = "DFAFDFAFDFAFDFAFCFAFCFAFCFAFCFAF";
char channel_1_notes[] = "AAAAAAFDAAAAAAFACCCCCCFFCCCCCCFF";
unsigned int note_count = 32;

unsigned int channel_0_tones[32];
unsigned int channel_1_tones[32];

void initialize_psg_channels() {
	set_psg(8, 16);
	set_psg(9, 16);
	set_psg(11, 0x88);
	set_psg(12, 0x13);
	set_psg(13, 0);
}

void build_ship_sequence(
      game_sprite* sprite_seq, unsigned char count, 
      unsigned int color, unsigned int sprite_pattern,
      unsigned int x_step, int* y_seq, unsigned int* explosion_patterns, unsigned char explosion_count) {
  int x = 0;
  for(unsigned int index=0; index < count; index++) {
    x = x + x_step;
    init_game_sprite(
      &sprite_seq[index], index+10, x, y_seq[index], color, sprite_pattern, 1, explosion_patterns, explosion_count);
  }
}

void build_ship_seq_idx(int* seq_seq_idx, unsigned char count, unsigned int idx_step) {
  int seq_idx = 0;
  for(unsigned int index=0; index < count; index++) {
    seq_seq_idx[index] = seq_idx;
    seq_idx = seq_idx + idx_step;
  }
}

void build_seq_func_1(int* num_seq, unsigned char count) {
  unsigned char pivot = count / 2;
  for (unsigned char index=0; index < pivot; index++) {
    num_seq[index] = 1;
    num_seq[index + pivot] = -1;
  }
}

void build_seq_func_2(int* num_seq, unsigned char count) {
  unsigned char pivot = count / 4;
  for (unsigned char index=0; index < pivot; index++) {
    num_seq[index] = 0;
    num_seq[index + pivot] = -1;
    num_seq[index + 2 * pivot] = 0;
    num_seq[index + 3 * pivot] = -1;
  }
}

void build_seq_func_3(int* num_seq, unsigned char count) {
  float cos_seq[] = {3.0, 2.94, 2.76, 2.49, 2.1, 1.65, 1.14, 0.57, 0.0, -0.57, -1.14, -1.65, -2.1, -2.49, -2.76, -2.94, -3.0};
  unsigned char idx = 0;
  float step = 17.0 / count;
  float cos_idx = 0.0;
  while (idx < 17) {
    num_seq[idx] = cos_seq[(int)cos_idx];
    idx = idx + 1;
    cos_idx = cos_idx + step;
  }
}

void build_seq_func_zero(int* num_seq, unsigned char count) {
  for (unsigned char index=0; index < count; index++) {
    num_seq[index] = 0;
  }
}

///////////////////// enemy ship sequences ///////////////////////

unsigned char explosion_patterns[] = {10, 11, 12, 13, 12, 11, 10};
unsigned char explosion_pattern_count = 7;

int seq1_move[128];
int seq2_move[128];
int seq3_move[128];
int seq4_move[128];

void init_move_seqs() {
  build_seq_func_1(&seq1_move, 128);
  build_seq_func_2(&seq2_move, 128);
  build_seq_func_3(&seq3_move, 128);
  build_seq_func_zero(&seq4_move, 128);
}

///////////////////// seq1 //////////////////////////

unsigned char seq1_ship_count = 3;
game_sprite seq1_ships[3];
int seq1_x_seq_idx[3]; 
int seq1_y_seq_idx[3];

void init_enemy_ship_seq_1(ship_sequence * seq) {
  int y_seq[] = { -30, -10, 10 };
  build_ship_sequence(
    &seq1_ships, 3, 12, 1,
    64, &y_seq, explosion_patterns, explosion_pattern_count);

  unsigned char seq1_count = 128;

  build_ship_seq_idx(&seq1_x_seq_idx, 3, 5);
  build_ship_seq_idx(&seq1_y_seq_idx, 3, 5);

  init_ship_sequence(seq, &seq1_ships, seq1_ship_count, &seq1_move, &seq2_move, seq1_count, &seq1_x_seq_idx, &seq1_y_seq_idx);
}

///////////////////// seq2 //////////////////////////

unsigned char seq2_ship_count = 5;
game_sprite seq2_ships[5];
int seq2_x_seq_idx[5]; 
int seq2_y_seq_idx[5];

void init_enemy_ship_seq_2(ship_sequence * seq) {
  int y_seq[] = { -50, -40, -30, -20, -16 };
  build_ship_sequence(
    &seq2_ships, 5, 13, 3,
    50, &y_seq, explosion_patterns, explosion_pattern_count);

  unsigned char seq2_count = 128;
  build_ship_seq_idx(&seq2_x_seq_idx, 5, 5);
  build_ship_seq_idx(&seq2_y_seq_idx, 5, 5);

  init_ship_sequence(seq, &seq2_ships, seq2_ship_count, &seq3_move, &seq2_move, seq2_count, &seq2_x_seq_idx, &seq2_y_seq_idx);
}

///////////////////// seq3 //////////////////////////

unsigned char seq3_ship_count = 4;
game_sprite seq3_ships[4];
int seq3_x_seq_idx[4]; 
int seq3_y_seq_idx[4];

void init_enemy_ship_seq_3(ship_sequence * seq) {
  int y_seq[] = { -50, -40, -30, -20, -16 };
  build_ship_sequence(
    &seq3_ships, 4, 8, 4,
    60, &y_seq, explosion_patterns, explosion_pattern_count);

  unsigned char seq3_count = 128;
  build_ship_seq_idx(&seq3_x_seq_idx, 4, 5);
  build_ship_seq_idx(&seq3_y_seq_idx, 4, 5);

  init_ship_sequence(seq, &seq3_ships, seq3_ship_count, &seq2_move, &seq4_move, seq3_count, &seq3_x_seq_idx, &seq3_y_seq_idx);
}


///////////////////// seq4 //////////////////////////

unsigned char seq4_ship_count = 3;
game_sprite seq4_ships[3];
int seq4_x_seq_idx[3]; 
int seq4_y_seq_idx[3];

void init_enemy_ship_seq_4(ship_sequence * seq) {
  int y_seq[] = { -40, -35, -30 };
  build_ship_sequence(&seq4_ships, 3, 5, 1,
    70, &y_seq, explosion_patterns, explosion_pattern_count);

  build_ship_seq_idx(&seq4_x_seq_idx, 3, 5);
  build_ship_seq_idx(&seq4_y_seq_idx, 3, 5);


  unsigned char seq4_count = 128;
  
  init_ship_sequence(seq, &seq4_ships, seq4_ship_count, &seq3_move, &seq2_move, seq4_count, &seq4_x_seq_idx, &seq4_y_seq_idx);
}

///////////////////// seq5 //////////////////////////

unsigned char seq5_ship_count = 6;
game_sprite seq5_ships[6];
int seq5_x_seq_idx[6]; 
int seq5_y_seq_idx[6];

void init_enemy_ship_seq_5(ship_sequence * seq) {
  int y_seq[] = {-40, -35, -30, -25, -20, -15};
  build_ship_sequence(&seq5_ships, 6, 13, 5,
    40, &y_seq, explosion_patterns, explosion_pattern_count);

  build_ship_seq_idx(&seq5_x_seq_idx, 6, 10);
  build_ship_seq_idx(&seq5_y_seq_idx, 6, 10);

  unsigned char seq5_count = 128;  
  init_ship_sequence(seq, &seq5_ships, seq5_ship_count, &seq3_move, &seq3_move, seq5_count, &seq5_x_seq_idx, &seq5_y_seq_idx);
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

    ////////////////// ASCII PATTERN COLORS ///////////////////

    screen_1_set_ascii_block_color(2,  4, 1, vdp_vwrite);
    screen_1_set_ascii_block_color(3,  15, 1, vdp_vwrite);    

    ////////////////// WRITE SCREEN 1 TILES ///////////////////

    screen_1_fill_with_chars(screen_1_tiles_with_stars_and_planet, vdp_vwrite); 
    
    /////////////////// SETUP ENEMY SHIP SEQUENCE /////////////   
    ship_sequence sequences[5];
    init_move_seqs();
    init_enemy_ship_seq_1(&sequences[0]);
    init_enemy_ship_seq_2(&sequences[1]);
    init_enemy_ship_seq_3(&sequences[2]);
    init_enemy_ship_seq_4(&sequences[3]);
    init_enemy_ship_seq_5(&sequences[4]);
    
    unsigned char sequence_idx = 0;
    unsigned char sequence_count = 5;

    int scene_finished[] = {0, 0};
    unsigned char scene_idx = 0;
    ///////////////////////////////////////////////////////////

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

      ship_sequence_run(&sequences[sequence_idx], vdp_put_sprite_16);

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

      ship_sequence_collision(&player_shoot, &sequences[sequence_idx], vdp_put_sprite_16);

      int end_of_sequence = sequences[sequence_idx].end_of_sequence;
      if ((sequence_idx < sequence_count - 1)&&(end_of_sequence == 1)) {
        sequence_idx++;
      }
    }
}
