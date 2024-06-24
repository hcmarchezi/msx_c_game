#include "ship_sequence.h"

void ship_sequence_update_position(ship_sequence* seq) {
  for (unsigned char idx=0; idx < seq->ship_count; idx++) {
    if (seq->ships[idx].y < 200) {
      seq->ships[idx].x += seq->x_seq[ seq->x_seq_idx[idx] ];
      seq->ships[idx].y += seq->y_seq[ seq->y_seq_idx[idx] ];

      if (seq->x_seq_idx[idx] < 32)
        seq->x_seq_idx[idx]++;
      else
        seq->x_seq_idx[idx] = 0;

      if (seq->y_seq_idx[idx] < 32)
        seq->y_seq_idx[idx]++;
      else
        seq->y_seq_idx[idx] = 0;
    }
  }
}

void ship_sequence_display(
    ship_sequence* seq,
    void (*ptr_put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int) ) {
  unsigned char ship_display_count = 0;
  for (unsigned char idx=0; idx < seq->ship_count; idx++) {
    if (seq->ships[idx].y < 200) {
      game_sprite_display(&seq->ships[idx], ptr_put_sprite_16);
      game_sprite_move(&seq->ships[idx], 5);
      ship_display_count++;
    }
  }
  if (ship_display_count == 0) {
    seq->end_of_sequence = 1;
  }
}

void ship_sequence_run(
    ship_sequence* seq,
    void (*ptr_put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int) ) {
  ship_sequence_update_position(seq);
  ship_sequence_display(seq, ptr_put_sprite_16);
}