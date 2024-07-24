#!/bin/bash
rm main_msx_game.c.bin
rm main_msx_game.c.cas

./compile.sh main_msx_game.c msxgame/game_sprite.c msxgame/music_tones.c msxgame/screen_1_tiling.c msxgame/game_sprite_collision.c msxgame/ship_sequence.c msxgame/ship_move_sequence.c game/ship_sprite.c game/ship_sequence.c
