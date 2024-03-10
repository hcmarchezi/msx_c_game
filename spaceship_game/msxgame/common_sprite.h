#ifndef COMMON_SPRITE_H
#define COMMON_SPRITE_H

typedef struct {
    int x;
    int y;
} position;

typedef struct {
    unsigned int start;
    unsigned int end;
} pattern_range;

typedef struct {
    unsigned int pattern;
    unsigned int color;
} pattern_color;

typedef struct {
    unsigned int psg_reg; // PSG register
    unsigned int psg_val; // PSG value
    unsigned int psg_vol; // PSG volume (channel C)
} noise_instruction;

#endif