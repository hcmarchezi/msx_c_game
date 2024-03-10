#include "sprite_swarm.h"

#include<stdlib.h>
#include<stdio.h>

sprite_swarm* create_enemy_ships(int cols, int rows, int xi, int yi, char initial_sprite_id) {
    int total_sprites = rows * cols;
    sprite_swarm* swarm = (sprite_swarm*)malloc(sizeof(sprite_swarm));
    swarm->array = (sprite_type**)malloc(total_sprites * sizeof(sprite_type*));
    swarm->size = cols * rows;
    int x = xi;
    int y = yi;
    char sprite_id = initial_sprite_id;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            sprite_type* sprite = create_sprite(sprite_id, x, y, 15, 3);
            swarm->array[row * cols + col] = sprite;
            x = x + 20; 
            sprite_id++;
        }
        y = y + 20;
        x = 50;
    }
    return swarm;
}

void free_enemy_ships(sprite_swarm* swarm) {
    for (unsigned int index=0; index < swarm->size; index++) {
        free(swarm->array[index]);
    }
    free(swarm);
}


void enemy_ships_move(sprite_swarm* swarm, char dx, char dy) {
    for (unsigned int index=0; index < swarm->size; index++) {
        swarm->array[index]->pos.x += dx;
        swarm->array[index]->pos.y += dy;
    }
}

unsigned char display_enemy_ships(
        sprite_swarm* swarm, 
        void (*put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int)) {

    for(unsigned char idx = 0; idx < swarm->size; idx++) {
        put_sprite_16(
            swarm->array[idx]->sprite_id,
            swarm->array[idx]->pos.x,
            swarm->array[idx]->pos.y,
            swarm->array[idx]->color,
            swarm->array[idx]->sprite_pattern);
    }

    return 0; 
}

