#!/bin/bash
echo 'compiling MSX as rom with ' $1
COMPILER=zcc
$COMPILER +msx -subtype=rom -llib3d  -lm -lndos -create-app -DAMALLOC -o$1.bin $1 -lmsxbios 

