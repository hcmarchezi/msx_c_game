#ifndef ANIMATION_SPRITE_H
#define ANIMATION_SPRITE_H

#include "common_sprite.h"

typedef struct {
	position pos;
    unsigned int sprite_id;
    
    unsigned int* patterns;
    unsigned int* colors;
    unsigned int  pattern_idx;
    unsigned int  pattern_count;

    noise_instruction** sound_cmds;

} animation_sprite;


noise_instruction* create_sound_instr(unsigned int psg_reg, unsigned int psg_val, unsigned int psg_vol);


animation_sprite* create_animation_sprite(
	position pos, unsigned int sprite_id, 
	unsigned int* patterns, unsigned int* colors, unsigned int pattern_count,
    noise_instruction** sound_cmds);

void free_animation_sprite(animation_sprite* sprite);

void animation_sprite_next_pattern(animation_sprite* sprite);

void animation_sprite_display(animation_sprite* sprite, void (*put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int));

void animation_sprite_sound(animation_sprite* sprite, void (*set_psg)(unsigned int, unsigned int)); 

char animation_sprite_has_next_pattern(animation_sprite* sprite);

#endif