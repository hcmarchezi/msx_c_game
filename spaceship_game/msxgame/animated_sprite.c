#include "animated_sprite.h"

#include <stdlib.h>
#include <stdio.h>

animated_sprite_type* create_animated_sprite(
    position pos, int step, char horizontal_orientation, unsigned int sprite_id, 
    pattern_range move_right_patterns,
    pattern_range move_left_patterns,
    pattern_collection left_poses_patterns,
    pattern_collection right_poses_patterns) {
        animated_sprite_type* sprite = (animated_sprite_type*)malloc(sizeof(animated_sprite_type));
        sprite->pos = pos;
        sprite->step = step;
        sprite->horizontal_orientation = horizontal_orientation;
        sprite->sprite_id = sprite_id;
        sprite->move_right_patterns = move_right_patterns;
        sprite->move_left_patterns = move_left_patterns;
        sprite->right_poses_patterns = right_poses_patterns;
        sprite->left_poses_patterns  = left_poses_patterns;
        sprite->jump_status = 'G';
        return sprite;
}

void free_animated_sprite(animated_sprite_type* animated_sprite) {
    free(animated_sprite);
}

void animated_sprite_move_right(animated_sprite_type* animated_sprite) {
    if (animated_sprite->pattern_idx < animated_sprite->move_right_patterns.start || 
        animated_sprite->pattern_idx > animated_sprite->move_right_patterns.end) {
            animated_sprite->pattern_idx = animated_sprite->move_right_patterns.start;
            animated_sprite->horizontal_orientation = 'R';
    } else {
        animated_sprite->pattern_idx++; 
        if (animated_sprite->pattern_idx > animated_sprite->move_right_patterns.end) {
            animated_sprite->pattern_idx =  animated_sprite->move_right_patterns.start;
        }
    }
    animated_sprite->pos.x = animated_sprite->pos.x + animated_sprite->step;
}

void animated_sprite_move_left(animated_sprite_type* animated_sprite) {
    if (animated_sprite->pattern_idx < animated_sprite->move_left_patterns.start ||
        animated_sprite->pattern_idx > animated_sprite->move_left_patterns.end) {
            animated_sprite->pattern_idx = animated_sprite->move_left_patterns.start;
            animated_sprite->horizontal_orientation = 'L';
    } else {
        animated_sprite->pattern_idx++; 
        if (animated_sprite->pattern_idx > animated_sprite->move_left_patterns.end) {
            animated_sprite->pattern_idx =  animated_sprite->move_left_patterns.start;
        }
    }
    animated_sprite->pos.x = animated_sprite->pos.x - animated_sprite->step;
}

void animated_sprite_move_down(animated_sprite_type* animated_sprite) {
    if (animated_sprite->horizontal_orientation == 'R') {
        animated_sprite->pattern_idx = animated_sprite->right_poses_patterns.down;

    } else if (animated_sprite->horizontal_orientation == 'L') {
        animated_sprite->pattern_idx = animated_sprite->left_poses_patterns.down;
    } else {

    }
}

void animated_sprite_move_up(animated_sprite_type* animated_sprite) {
    if (animated_sprite->horizontal_orientation == 'R') {
        animated_sprite->pattern_idx = animated_sprite->move_right_patterns.start;

    } else if (animated_sprite->horizontal_orientation == 'L') {
        animated_sprite->pattern_idx = animated_sprite->move_left_patterns.start;
    } else {

    }
}

void animated_sprite_kick(animated_sprite_type* animated_sprite) {
    char horz_orientation = animated_sprite->horizontal_orientation;
    char jump_status = animated_sprite->jump_status;

    if (animated_sprite->horizontal_orientation == 'R') {
        if (animated_sprite->jump_status == 'G') {
            animated_sprite->pattern_idx = animated_sprite->right_poses_patterns.ground_kick;
        } else if (animated_sprite->jump_status == 'U') {
            animated_sprite->pattern_idx = animated_sprite->right_poses_patterns.up_kick;
        } else { //'D' - crouch
            animated_sprite->pattern_idx = animated_sprite->right_poses_patterns.down_kick;
        }

    } else if (animated_sprite->horizontal_orientation == 'L') {
        if (animated_sprite->jump_status == 'G') {
            animated_sprite->pattern_idx = animated_sprite->left_poses_patterns.ground_kick;
        } else if (animated_sprite->jump_status == 'U') {
            animated_sprite->pattern_idx = animated_sprite->left_poses_patterns.up_kick;
        } else { // 'D' - crouch
            animated_sprite->pattern_idx = animated_sprite->left_poses_patterns.down_kick;
        }   
    } else {

    }
}
