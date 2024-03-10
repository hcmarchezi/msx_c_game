#include <msx/gfx.h>
#include <msx.h>
#include <psg.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "data/sprites.h"
#include "data/tiles.h"
#include "msxgame/game_sprite.h"
#include "msxgame/music_tones.h"
#include "msxgame/screen_1_tiling.h"
#include "msxgame/msx_psg_helper.h"
#include "msxgame/game_sprite_collision.h"


#define ENEMY_SIZE 3

game_sprite player;
game_sprite player_shoot;

game_sprite* enemies[ENEMY_SIZE];

char channel_0_notes[] = "DFAFDFAFDFAFDFAFCFAFCFAFCFAFCFAF";
char channel_1_notes[] = "AAAAAAFDAAAAAAFACCCCCCFFCCCCCCFF";
unsigned int note_count = 32;

unsigned int channel_0_tones[32];
unsigned int channel_1_tones[32];

void initialize_psg_channels() {
	set_psg(8, 16);
	set_psg(9, 16);
	set_psg(11, 0x88);
	set_psg(12, 0x13);
	set_psg(13, 0);
}

void reset_enemy_position(game_sprite* sprite) {
	int collided_x = rand() % 20 * 12;
	int collided_y = 0;
	sprite->x = collided_x;
	sprite->y = collided_y;
}

game_sprite* init_enemy_sprite(unsigned int sprite_id) {
	game_sprite* enemy = (game_sprite *) malloc(sizeof(game_sprite));
    int x = rand() % 10 * 25;
    int y = rand() % 5 * 10;
    create_game_sprite(enemy, sprite_id, x, y, 12, 1, 1);
    return enemy;
}

void main() {
    set_color(15, 1, 1);
    set_mode(mode_1);
    set_sprite_mode(sprite_large);

    ///////////////// SPRITE PATTERN DEFINITIONS /////////////

    set_sprite_16(0, player_pattern);
    set_sprite_16(1, enemy_pattern);
    set_sprite_16(2, player_shoot_pattern);

    set_sprite_16(10, explosion_1_pattern);
    set_sprite_16(11, explosion_2_pattern);
    set_sprite_16(12, explosion_3_pattern);
    set_sprite_16(13, explosion_4_pattern);

    ////////////////// ASCII PATTERN DEFINITIONS //////////////

    screen_1_set_tile_patterns(0x10, 0x13, planet_pattern, vpoke);
    screen_1_set_tile_patterns(0x14, 0x17, moon_pattern, vpoke);
    screen_1_set_tile_patterns(0x18, 0x1B, stars_pattern, vpoke);

    ////////////////// ASCII PATTERN COLORS ///////////////////

    screen_1_set_tile_colors(2,  8, 0, vpoke);
    screen_1_set_tile_colors(3, 15, 0, vpoke);

    ////////////////// WRITE SCREEN 1 TILES ///////////////////

    screen_1_write_screen_tiles_char(screen_1_tiles_with_stars_and_planet, vpoke);

    ///////////////////////////////////////////////////////////

    for (int index=0; index < ENEMY_SIZE; index++) {
    	enemies[index] = init_enemy_sprite(index + 10);  
    }
	    
    create_game_sprite(&player, 0, 128, 170, 15, 0, 1);
    create_game_sprite(&player_shoot, 2, 128, -20, 6, 2, 1);

    sprite_collision player_shoot_collision;
    create_sprite_collision(&player_shoot_collision, &player_shoot, enemies, ENEMY_SIZE);

    music_tones tones;
    map_notes_to_tones(3, channel_0_notes, note_count, channel_0_tones);
	map_notes_to_tones(4, channel_1_notes, note_count, channel_1_tones);
	create_music_tones(&tones, channel_0_tones, channel_1_tones, note_count);

    clock_t start_t = clock();
    clock_t end_t = clock();

    for (;;) {
    	
		int stick = get_stick(0);
    	game_sprite_move(&player, stick); 
    	game_sprite_display(&player, msx_put_sprite_16);
    	game_sprite_display(&player_shoot, msx_put_sprite_16);

    	for (int index=0; index < ENEMY_SIZE; index++) {
    		if (enemies[index]->y > 191) {
    			enemies[index]->x = rand() % 20 * 12;
    			enemies[index]->y = 0;
    		}
    		game_sprite_display(enemies[index], msx_put_sprite_16);
    		game_sprite_move(enemies[index], 5); // 5 -> down
    	}

    	if (get_trigger(0) && player_shoot.y == -20) {
    		set_psg(10, 15);
    		player_shoot.y = player.y - 16;
    		player_shoot.x = player.x;
    	}    	

    	player_shoot.y -= 5;

    	if (player_shoot.y < -20) {
    		set_psg(10, 0);
    		player_shoot.y = -20;
    	} else {
    		set_psg(4, player_shoot.y + 51);
    		set_psg(5, 1);
    	}

    	game_sprite_display(&player_shoot, msx_put_sprite_16);

    	if ((long)(end_t - start_t) > 10) {
    		initialize_psg_channels();
    		music_tones_play_tone(&tones, 0, &set_psg);
    		music_tones_play_tone(&tones, 1, &set_psg);
    	 	music_tones_next_tone(&tones);
    	 	start_t = clock();
    	 	end_t = clock();
    	} else {
    		end_t = clock();
    	}

    	sprite_collision_check(&player_shoot_collision);
    	for (int idx=0; idx < player_shoot_collision.to_many_count; idx++) {
    		if (player_shoot_collision.collision[idx] == 1) {
    			printf("sprite_idx=%d \n", idx);

				game_sprite* collided_sprite = player_shoot_collision.to_many[idx];
				reset_enemy_position(collided_sprite);
    			
    			player_shoot.y = -20;
    		}
    	}
    	sprite_collision_clear(&player_shoot_collision);
    }
}