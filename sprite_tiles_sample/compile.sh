#!/bin/bash
zcc +msx -llib3d  -lm -lndos -create-app -DAMALLOC -DGRAPHICS -o$1.bin $1 -lmsxbios

