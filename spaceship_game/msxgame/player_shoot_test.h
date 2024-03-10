#include "minunit/minunit.h"
#include "player_shoot.h"
#include "common_sprite.h"

MU_TEST(test_create_player_shoot) {
	unsigned int sprite_id = 5;
	int x = 150;
	int y = 120;
	unsigned int color = 11;
	unsigned int sprite_pattern = 10;
	int dy = -3;
	
	sprite_type* sprite = create_sprite(sprite_id, x, y, color, sprite_pattern);	
	player_shoot* shoot = create_player_shoot(sprite, dy);

	mu_check(shoot->sprite->sprite_id == 5);
	mu_check(shoot->sprite->pos.x == x);
	mu_check(shoot->sprite->pos.y == y);
	mu_check(shoot->sprite->color == 11);
	mu_check(shoot->sprite->sprite_pattern == 10);
	mu_check(shoot->dy == -3);

	free_player_shoot(shoot);
}

MU_TEST(test_update_player_shoot_position_when_shooting) {
	int x = 150;
	int y = 120;
	int dy = -3;
	
	sprite_type* sprite = create_sprite(5, x, y, 11, 1);	
	player_shoot* shoot = create_player_shoot(sprite, dy);

	player_shoot_update_position(shoot);

	mu_check(shoot->sprite->pos.x == 150);
	mu_check(shoot->sprite->pos.y == 117);
	mu_check(shoot->dy == -3);

	free_player_shoot(shoot);
}

MU_TEST(test_update_player_shoot_position_when_not_shooting) {
	int x = 150;
	int y = 200;
	int dy = -3;
	
	sprite_type* sprite = create_sprite(5, x, y, 11, 1);	
	player_shoot* shoot = create_player_shoot(sprite, dy);

	player_shoot_update_position(shoot);

	mu_check(shoot->sprite->pos.x == 150);
	mu_check(shoot->sprite->pos.y == 200);
	mu_check(shoot->dy == -3);

	free_player_shoot(shoot);
}

MU_TEST(test_set_player_shoot_position) {
	int x = 120;
	int y = 150;
	int dy = -3;
	
	sprite_type* sprite = create_sprite(5, x, y, 11, 1);	
	player_shoot* shoot = create_player_shoot(sprite, dy);

	position pos; pos.x = 180; pos.y = 100;
	player_shoot_set_position(shoot, pos);

	mu_check(shoot->sprite->pos.x == 180);
	mu_check(shoot->sprite->pos.y == 100);
	mu_check(shoot->dy == -3);

	free_player_shoot(shoot);
}

void shoot_put_sprite_16(unsigned int sprite_id, int x, int y, unsigned int color, unsigned int pattern) {
	mu_check(sprite_id == 5);
	mu_check(x == 150);
	mu_check(y == 120);
	mu_check(color == 11);
	mu_check(pattern == 10);
}

MU_TEST(test_player_shoot_display) {
	unsigned int sprite_id = 5;
	int x = 150;
	int y = 120;
	unsigned int color = 11;
	unsigned int sprite_pattern = 10;
	int dy = -3;
	
	sprite_type* sprite = create_sprite(sprite_id, x, y, color, sprite_pattern);	
	player_shoot* shoot = create_player_shoot(sprite, dy);

	unsigned char result = display_player_shoot(shoot, shoot_put_sprite_16);

	mu_check(result == 0);
}

MU_TEST_SUITE(player_shoot_test_suite) {
  	MU_RUN_TEST(test_create_player_shoot);
  	MU_RUN_TEST(test_update_player_shoot_position_when_shooting);
  	MU_RUN_TEST(test_update_player_shoot_position_when_not_shooting);
  	MU_RUN_TEST(test_set_player_shoot_position);
  	MU_RUN_TEST(test_player_shoot_display);
}
