#include <stdio.h>
#include "gmxa/fileio/xtcio.h"

int main(int argc, char* argv[]){

    XTC* xp;
    xp = openXtc(argv[1], argv[2]);

for(int step = 0; readXtc(xp, step); step += 50){   /* per step num is 50*/
	printf(" no title\n");
        printf("%5d\n", (*xp).data.natoms);
        for(int i = 0; i < (*xp).data.natoms; i++ ){
            printf("%5d%-5s%5s%5d%8.3lf%8.3lf%8.3lf\n", (*xp).index[i].resid, (*xp).index[i].resname, (*xp).index[i].atomname, (*xp).index[i].atomid, (*xp).index[i].x, (*xp).index[i].y, (*xp).index[i].z);
        }
        printf("%10.5lf%10.5lf%10.5lf\n", (*xp).data.xbox, (*xp).data.ybox, (*xp).data.zbox);
    }
    
    closeXtc(xp);

    return 0;
}
