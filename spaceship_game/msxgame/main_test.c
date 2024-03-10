#include "minunit/minunit.h"
#include "sprite_type_test.h"
#include "sprite_swarm_test.h"
#include "animated_sprite_test.h"
#include "animation_sprite_test.h"
#include "music_track_test.h"
#include "game_sprite_test.h"
#include "player_shoot_test.h"
#include "simple_music_test.h"
#include "screen_1_tiling_test.h"
#include "music_tones_test.h"
#include "msx_psg_helper_test.h"
#include "game_sprite_collision_test.h"
#include "game_sprite_explosion_test.h"


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