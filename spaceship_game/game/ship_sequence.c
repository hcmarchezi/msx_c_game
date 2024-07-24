#include "ship_sequence.h"

#include "ship_sprite.h"

#include "../data/game_ship_movement.h"

#include<stdlib.h>

game_sprite ship_sequence_1_sprite_1;
game_sprite ship_sequence_1_sprite_2;
game_sprite ship_sequence_1_sprite_3;

void new_ship_sequence_1(ship_sequence* seq) {  
  create_ship_sprite_1(&ship_sequence_1_sprite_1, 10,  50, -40, 12);
  create_ship_sprite_1(&ship_sequence_1_sprite_2, 11, 150, -30, 13);
  create_ship_sprite_1(&ship_sequence_1_sprite_3, 12, 200, -20, 12);

  seq->ships[0] = &ship_sequence_1_sprite_1;
  seq->ships[1] = &ship_sequence_1_sprite_2;
  seq->ships[2] = &ship_sequence_1_sprite_3;

  seq->x_seq_idx[0] = 10; seq->x_seq_idx[1] = 20; seq->x_seq_idx[2] = 30;
  seq->y_seq_idx[0] = 40; seq->y_seq_idx[1] = 50; seq->y_seq_idx[2] = 60;

  seq->ship_count = 3;

  seq->x_seq = move_sequence_1;
  seq->y_seq = move_sequence_2;

  seq->seq_count = 128;

  seq->end_of_sequence = 0; // boolean
}

game_sprite ship_sequence_2_sprite_1;
game_sprite ship_sequence_2_sprite_2;
game_sprite ship_sequence_2_sprite_3; 
game_sprite ship_sequence_2_sprite_4; 
game_sprite ship_sequence_2_sprite_5;

void new_ship_sequence_2(ship_sequence* seq) {
  create_ship_sprite_2(&ship_sequence_2_sprite_1, 10,   0, -40, 10);
  create_ship_sprite_2(&ship_sequence_2_sprite_2, 11,  50, -35, 12);
  create_ship_sprite_2(&ship_sequence_2_sprite_3, 12, 100, -30, 10);
  create_ship_sprite_2(&ship_sequence_2_sprite_4, 13, 150, -25, 12);
  create_ship_sprite_2(&ship_sequence_2_sprite_5, 14, 200, -20, 10);

  seq->ships[0] = &ship_sequence_2_sprite_1;
  seq->ships[1] = &ship_sequence_2_sprite_2;
  seq->ships[2] = &ship_sequence_2_sprite_3;
  seq->ships[3] = &ship_sequence_2_sprite_4;
  seq->ships[4] = &ship_sequence_2_sprite_5;

  seq->x_seq_idx[0] = 10; seq->x_seq_idx[1] = 20; seq->x_seq_idx[2] = 30;
  seq->x_seq_idx[3] = 40; seq->x_seq_idx[4] = 50;

  seq->y_seq_idx[0] = 40; seq->y_seq_idx[1] = 50; seq->y_seq_idx[2] = 60;
  seq->y_seq_idx[3] = 70; seq->y_seq_idx[4] = 80;

  seq->ship_count = 5;

  seq->x_seq = move_sequence_3;
  seq->y_seq = move_sequence_2;

  seq->seq_count = 128;

  seq->end_of_sequence = 0; // boolean
} 

game_sprite ship_sequence_3_sprite_1;
game_sprite ship_sequence_3_sprite_2;
game_sprite ship_sequence_3_sprite_3; 
game_sprite ship_sequence_3_sprite_4; 
game_sprite ship_sequence_3_sprite_5;
game_sprite ship_sequence_3_sprite_6;

void new_ship_sequence_3(ship_sequence* seq) {
  create_ship_sprite_3(&ship_sequence_3_sprite_1, 10,   0, -40, 13);
  create_ship_sprite_3(&ship_sequence_3_sprite_2, 11,  40, -20, 12);
  create_ship_sprite_3(&ship_sequence_3_sprite_3, 12,  80, -40,  5);
  create_ship_sprite_3(&ship_sequence_3_sprite_4, 13, 120, -20,  5);
  create_ship_sprite_3(&ship_sequence_3_sprite_5, 14, 160, -40, 12);
  create_ship_sprite_3(&ship_sequence_3_sprite_6, 15, 200, -20, 13);

  seq->ships[0] = &ship_sequence_3_sprite_1;
  seq->ships[1] = &ship_sequence_3_sprite_2;
  seq->ships[2] = &ship_sequence_3_sprite_3;
  seq->ships[3] = &ship_sequence_3_sprite_4;
  seq->ships[4] = &ship_sequence_3_sprite_5;
  seq->ships[5] = &ship_sequence_3_sprite_6;

  seq->x_seq_idx[0] = 10; seq->x_seq_idx[1] = 20; seq->x_seq_idx[2] = 30;
  seq->x_seq_idx[3] = 40; seq->x_seq_idx[4] = 50; seq->x_seq_idx[5] = 60;

  seq->y_seq_idx[0] = 40; seq->y_seq_idx[1] = 50; seq->y_seq_idx[2] = 60;
  seq->y_seq_idx[3] = 70; seq->y_seq_idx[4] = 80; seq->y_seq_idx[5] = 90;

  seq->ship_count = 6;

  seq->x_seq = move_sequence_zero;
  seq->y_seq = move_sequence_2;

  seq->seq_count = 128;

  seq->end_of_sequence = 0; // boolean
}

game_sprite ship_sequence_4_sprite_1;
game_sprite ship_sequence_4_sprite_2;
game_sprite ship_sequence_4_sprite_3; 
game_sprite ship_sequence_4_sprite_4; 

void new_ship_sequence_4(ship_sequence* seq) {
  create_ship_sprite_4(&ship_sequence_4_sprite_1, 10,   0, -40, 13);
  create_ship_sprite_4(&ship_sequence_4_sprite_2, 11,  40, -20, 12);
  create_ship_sprite_4(&ship_sequence_4_sprite_3, 12,  80, -40,  5);
  create_ship_sprite_4(&ship_sequence_4_sprite_4, 13, 120, -20,  5);

  seq->ships[0] = &ship_sequence_4_sprite_1;
  seq->ships[1] = &ship_sequence_4_sprite_2;
  seq->ships[2] = &ship_sequence_4_sprite_3;
  seq->ships[3] = &ship_sequence_4_sprite_4;

  seq->x_seq_idx[0] = 10; seq->x_seq_idx[1] = 20; 
  seq->x_seq_idx[2] = 30; seq->x_seq_idx[3] = 40; 

  seq->y_seq_idx[0] = 40; seq->y_seq_idx[1] = 50; 
  seq->y_seq_idx[2] = 60; seq->y_seq_idx[3] = 70;

  seq->ship_count = 4;

  seq->x_seq = move_sequence_2;
  seq->y_seq = move_sequence_zero;

  seq->seq_count = 128;

  seq->end_of_sequence = 0; // boolean
}

char score_title[] = "SCORE: ";
char score[] = "        ";

void screen_1_init_score(void (*vdp_vwrite)(void*, unsigned int, unsigned int)) {
  vdp_vwrite((void*)score_title, 0x1800, 7);
}

void screen_1_print_score(int player_score, void (*vdp_vwrite)(void*, unsigned int, unsigned int)) {
  itoa(player_score, score, 10);
  vdp_vwrite((void*)score, 0x1807, 6);
}
