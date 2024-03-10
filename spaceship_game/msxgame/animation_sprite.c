#include "animation_sprite.h"

#include <stdlib.h>
#include <stdio.h>


noise_instruction* create_sound_instr(unsigned int psg_reg, unsigned int psg_val, unsigned int psg_vol) {
    noise_instruction* instr = (noise_instruction*)malloc(sizeof(noise_instruction));
    instr->psg_reg = psg_reg;
    instr->psg_val = psg_val;
    instr->psg_vol = psg_vol;
    return instr;
}


animation_sprite* create_animation_sprite(
		position pos, unsigned int sprite_id, 
		unsigned int* patterns, unsigned int* colors, unsigned int pattern_count,
		noise_instruction** sound_cmds) {
	animation_sprite* sprite = (animation_sprite*)malloc(sizeof(animation_sprite));
	sprite->pos = pos;
	sprite->sprite_id = sprite_id;
	sprite->patterns = patterns;
	sprite->colors = colors;
	sprite->pattern_count = pattern_count;
	sprite->pattern_idx = 0;
	sprite->sound_cmds = sound_cmds;
	return sprite;
}

void free_animation_sprite(animation_sprite* sprite) {
	// code
	free(sprite);
}

void animation_sprite_next_pattern(animation_sprite* sprite) {
	sprite->pattern_idx++;
}

void animation_sprite_display(animation_sprite* sprite, void (*ptr_put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int)) {
	ptr_put_sprite_16(
		sprite->sprite_id, sprite->pos.x, sprite->pos.y, 
		sprite->colors[sprite->pattern_idx], sprite->patterns[sprite->pattern_idx]);
}

void animation_sprite_sound(animation_sprite* sprite, void (*ptr_set_psg)(unsigned int, unsigned int)) {
	unsigned int psg_reg = sprite->sound_cmds[sprite->pattern_idx]->psg_reg;
	unsigned int psg_val = sprite->sound_cmds[sprite->pattern_idx]->psg_val;
	unsigned int psg_vol_channel_c = sprite->sound_cmds[sprite->pattern_idx]->psg_vol;
	unsigned int CHANNEL_C_VOLUME = 10;
	ptr_set_psg(psg_reg, psg_val);
	ptr_set_psg(CHANNEL_C_VOLUME, psg_vol_channel_c);
}

char animation_sprite_has_next_pattern(animation_sprite* sprite) {
	return sprite->pattern_idx < sprite->pattern_count - 1;
}