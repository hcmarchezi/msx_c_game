#!/bin/bash
COMPILER=zcc

X_CFLAGS="+msx -vn -lm -lndos -create-app -DAMALLOC -DGRAPHICS -Dspritesize=16 -DSOUND -compiler=sdcc -SO3"
Y_CFLAGS="+msx -create-app -lm -vn -DAMALLOC2 -lndos -DGRAPHICS"
CFLAGS="+msx -vn -lm -lndos -create-app -DAMALLOC2"


COMMAND="$COMPILER $CFLAGS -o$1.bin $1 $2 $3 $4 $5 -lmsxbios -pragma-define:CLIB_FIRMWARE_KEYBOARD_CLICK=0"

echo $COMMAND

$COMMAND

