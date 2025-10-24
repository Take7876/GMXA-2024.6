#include <stdio.h>
#include "gmxa/fileio/xtcio.h"

int main(int argc, char* argv[]){

    XTC* xp;
    xp = openXtc(argv[1], argv[2]);
    readXtc(xp, 100);
    for(int i = 0; i < (*xp).data.natoms; i++ )printf("%5d%-5s%5s%5d%8.3lf%8.3lf%8.3lf\n", (*xp).index[i].resid, (*xp).index[i].resname, (*xp).index[i].atomname, (*xp).index[i].atomid, (*xp).index[i].x, (*xp).index[i].y, (*xp).index[i].z);
    closeXtc(xp);

    return 0;
}
