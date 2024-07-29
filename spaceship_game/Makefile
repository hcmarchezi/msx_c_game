CFILES = \
		main_msx_game.c \
		$(wildcard game/*.c) \
		msxgame/game_sprite.c \
		msxgame/music_tones.c \
		msxgame/screen_1_tiling.c \
		msxgame/game_sprite_collision.c \
		msxgame/ship_sequence.c \
		msxgame/ship_move_sequence.c 

OBJFILES = $(CFILES:.c=.o)

OUT = spaceship
CC = zcc
CFLAGS = +msx -vn -lm -create-app -lndos -DAMALLOC -lmsxbios -pragma-define:CLIB_FIRMWARE_KEYBOARD_CLICK=0

$(OUT): $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o spaceship.bin

.PHONY: clean

clean:
	@echo "cleaning up..."
	rm -rvf *.cas *.bin *.o game/*.o msxgame/*.o
