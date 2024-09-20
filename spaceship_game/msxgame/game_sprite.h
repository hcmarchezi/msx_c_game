#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

typedef struct {
	unsigned int sprite_id;
	int x;
	int y;
    unsigned int color;
    unsigned int sprite_pattern;
    int velocity;

    unsigned char status; // A - active | E - exploding | D - destroyed
    unsigned int* explosion_pattern;
    unsigned char explosion_idx;
    unsigned char explosion_count;
    unsigned char* explosion_sound_tones;

} game_sprite;

void define_sprite_pattern(int sprite_pattern_id, const char* sprite_pattern, int (*vpoke)(int, int));

void init_game_sprite(
	game_sprite* sprite,
	unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern, 
	int velocity, unsigned int* explosion_pattern, unsigned char explosion_count);

game_sprite* new_game_sprite(
	unsigned int sprite_id, int x, int y, unsigned int color, unsigned int sprite_pattern, 
	int velocity, unsigned int* explosion_pattern, unsigned char explosion_count);

void game_sprite_move(game_sprite* ship, unsigned int stick);

void game_sprite_get_position(game_sprite* ship, int* x, int* y);

void game_sprite_display(
	game_sprite* ship, 
	void (*ptr_put_sprite_16)(unsigned int, int, int, unsigned int, unsigned int));

void game_sprite_set_explosion_mode(game_sprite* ship);

#endif