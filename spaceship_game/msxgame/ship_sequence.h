#ifndef SHIP_SEQUENCE_H
#define SHIP_SEQUENCE_H

#include "game_sprite.h"

typedef struct {
  game_sprite ships[16];
  unsigned char ship_count;
  int x_seq[32];
  int y_seq[32];

  int x_seq_idx[16];
  int y_seq_idx[16];

  int end_of_sequence; // boolean

} ship_sequence;


void ship_sequence_update_position(ship_sequence* seq);

void ship_sequence_display(
    ship_sequence* seq,
    void (*ptr_put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int));

void ship_sequence_run(
    ship_sequence* seq,
    void (*ptr_put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int) );

#endif