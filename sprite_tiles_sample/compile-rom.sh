#!/bin/bash
echo 'compiling MSX as rom with ' $1
zcc +msx -subtype=rom -llib3d  -lm -lndos -create-app -DAMALLOC -o$1.bin $1 -lmsxbios 

