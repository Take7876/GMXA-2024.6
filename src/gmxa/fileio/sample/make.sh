#!/bin/bash

# for mac and gromacs-2022 and later versions
#g++  -std=c++17 sample_xtc.c -I ../../../ -lgmxa -L ../../../../lib/ -lgromacs -L /Users/k.taketoshi/apl/gromacs-2023.4/lib/  -I /Users/k.taketoshi/src/gromacs-2023.4/src -I /Users/k.taketoshi/src/gromacs-2023.4/api/legacy/include -o sample_xtc.out
#export DYLD_LIBRARY_PATH=/Users/k.taketoshi/src/gromacs-2023.4/build/lib:$DYLD_LIBRARY_PATH


# for linux and gromacs-2021.7
g++ sample_xtc.c -I ../../../ -lgmxa -L ../../../../lib/ -lgromacs -L/home/taketoshi/apl/gromacs-2021.7/lib64  -I/home/taketoshi/src/gromacs-2021.7/src -o sample_xtc.out
#export LD_LIBRARY_PATH=/home/taketoshi/src/gromacs-2021.7/build/lib/:$LD_LIBRARY_PATH

