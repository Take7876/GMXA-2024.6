#!/bin/bash 

g++ sample_find.c -o sample_find.out  -lgmxa -L ../../../../lib/ -I ../../../
gcc -std=c11  sample_pbc.c -o sample_pbc.out  -lgmxa -L ../../../../lib/ -I ../../../
