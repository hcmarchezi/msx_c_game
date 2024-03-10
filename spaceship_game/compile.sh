#!/bin/bash
zcc +msx -llib3d  -lm -lndos -create-app -DAMALLOC -DGRAPHICS -o$1.bin $1 $2 $3 $4 $5 -lmsxbios -pragma-define:CLIB_FIRMWARE_KEYBOARD_CLICK=0

