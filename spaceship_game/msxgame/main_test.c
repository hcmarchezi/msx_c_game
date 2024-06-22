#include "minunit/minunit.h"
#include "test_sprite_type.h"
#include "test_sprite_swarm.h"
#include "test_animated_sprite.h"
#include "test_animation_sprite.h"
#include "test_music_track.h"
#include "test_game_sprite.h"
#include "test_player_shoot.h"
//#include "test_simple_music.h"
#include "test_screen_1_tiling.h"
#include "test_music_tones.h"
#include "test_msx_psg_helper.h"
#include "test_game_sprite_collision.h"
#include "test_game_sprite_explosion.h"


int main(int argc, char** argv) {
	printf("sprite_test_suite: ");
	MU_RUN_SUITE(sprite_test_suite);
	printf("\n");

	printf("sprite_swarm_test_suite: ");
	MU_RUN_SUITE(sprite_swarm_test_suite);
	printf("\n");

	printf("animated_sprite_test_suite: ");
	MU_RUN_SUITE(animated_sprite_test_suite);
    printf("\n");

	printf("animation_sprite_test_suite:  ");
	MU_RUN_SUITE(animation_sprite_test_suite);
	printf("\n");

	printf("music_track_test_suite: ");
	MU_RUN_SUITE(music_track_test_suite);
	printf("\n");

	printf("game_sprite_test_suite: ");
	MU_RUN_SUITE(game_sprite_test_suite);
	printf("\n");

	printf("player_shoot_test_suite: ");
	MU_RUN_SUITE(player_shoot_test_suite);
    printf("\n");

	// printf("simple_music_test_suite: ");
	// MU_RUN_SUITE(simple_music_test_suite);
    // printf("\n");

    printf("screen_1_tiling_test_suite: ");
    MU_RUN_SUITE(screen_1_tiling_test_suite);
    printf("\n");

    printf("music_tones_test_suite: ");
    MU_RUN_SUITE(music_tones_test_suite);
    printf("\n");

    printf("msx_psg_helper_test_suite: ");
    MU_RUN_SUITE(msx_psg_helper_test_suite);
    printf("\n");

    printf("game_sprite_collision_test_suite: ");
    MU_RUN_SUITE(game_sprite_collision_test_suite);
    printf("\n");

    printf("game_sprite_explosion_test: ");
    MU_RUN_SUITE(game_sprite_explosion_test_suite);
    printf("\n");

	MU_REPORT();
	return MU_EXIT_CODE;
}
