#!/bin/bash
COMPILER=zcc

CFLAGS="+msx -vn -lm -create-app -lndos -DAMALLOC "

COMMAND="$COMPILER $CFLAGS -o$1.bin $1 $2 $3 $4 $5 $6 $7 $8 $9 -lmsxbios -pragma-define:CLIB_FIRMWARE_KEYBOARD_CLICK=0"

echo $COMMAND

$COMMAND

