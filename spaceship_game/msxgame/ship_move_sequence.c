#include "ship_move_sequence.h"

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