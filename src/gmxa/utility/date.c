#include <stdio.h>
#include <time.h>

#include "gmxa/utility/date.h"

void date(FILE *fp){

    time_t now;
    time(&now);

    struct tm *local = localtime(&now);

    fprintf(fp, "# Creation time : %d-%02d-%02d %02d:%02d:%02d\n",
            (*local).tm_year + 1900,
            (*local).tm_mon + 1,
            (*local).tm_mday,
            (*local).tm_hour,
            (*local).tm_min,
            (*local).tm_sec);

    return;
}
