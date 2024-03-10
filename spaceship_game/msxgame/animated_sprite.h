#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "common_sprite.h"

typedef struct {
    unsigned int down;
    unsigned int up; 
    unsigned int ground_kick;
    unsigned int down_kick;
    unsigned int up_kick;
} pattern_collection;

typedef struct {
    position pos;
    int step;
    char horizontal_orientation; // L and R
    char jump_status; // G (ground), U (up - jumping) and D (down - crouching)

    unsigned int sprite_id;    
    unsigned int pattern_idx;   // current sprite pattern in use
    pattern_range move_right_patterns;
    pattern_range move_left_patterns;

    pattern_collection left_poses_patterns;
    pattern_collection right_poses_patterns;

} animated_sprite_type;

animated_sprite_type* create_animated_sprite(
    position pos, int step, char orientation, unsigned int sprite_id, 
    pattern_range move_right_patterns,
    pattern_range move_left_patterns,
    pattern_collection left_poses_patterns,
    pattern_collection right_poses_patterns);

void free_animated_sprite(animated_sprite_type* animated_sprite);

void animated_sprite_move_right(animated_sprite_type* animated_sprite);

void animated_sprite_move_left(animated_sprite_type* animated_sprite);

void animated_sprite_move_down(animated_sprite_type* animated_sprite);

void animated_sprite_move_up(animated_sprite_type* animated_sprite);

void animated_sprite_kick(animated_sprite_type* animated_sprite);

#endif