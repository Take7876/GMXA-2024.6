#!/bin/bash

# for mac and gromacs-2022 and later versions
#g++  -std=c++17 sample_xtc.c -I ../../../ -lgmxa -L ../../../../lib/ -lgromacs -L /write/your/directory  -I /write/your/directory -I /write/your/directory/src/gromacs-2023.4/api/legacy/include -o sample_xtc.out
#export DYLD_LIBRARY_PATH=/write/your/directory/src/gromacs-2023.4/build/lib:$DYLD_LIBRARY_PATH


# for linux and gromacs-2021.7
g++ sample_xtc.c -I ../../../ -lgmxa -L ../../../../lib/ -lgromacs -L/write/your/directory  -I/write/your/directory -o sample_xtc.out
#export LD_LIBRARY_PATH=/write/your/directory/src/gromacs-2021.7/build/lib/:$LD_LIBRARY_PATH

