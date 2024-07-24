#ifndef SHIP_SEQUENCE_1_H
#define SHIP_SEQUENCE_1_H

#include "../msxgame/ship_sequence.h"

void new_ship_sequence_1(ship_sequence* seq);

void new_ship_sequence_2(ship_sequence* seq);

void new_ship_sequence_3(ship_sequence* seq);

void new_ship_sequence_4(ship_sequence* seq);

void screen_1_init_score(void (*vdp_vwrite)(void*, unsigned int, unsigned int));

void screen_1_print_score(int player_score, void (*vdp_vwrite)(void*, unsigned int, unsigned int));

#endif