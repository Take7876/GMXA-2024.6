#include <stdio.h>
#include "gmxa/utility/pbc.h" 

#define INT_TEST
//#define DOUBLE_TEST
//#define UNMATCH_TYPE_TEST

int main() {
    
    #ifdef INT_TEST
        int prev_int = -5;
        int max_int = 10;
        int result_int = applyPeriodicBoundary(prev_int, max_int);
        printf("applyPeriodicBoundary_int(%d, %d) = %d\n", prev_int, max_int, result_int);
    #endif

    #ifdef DOUBLE_TEST
        double prev_double = -5.75;
        double max_double = 10.0;
        double result_double = applyPeriodicBoundary(prev_double, max_double);
        printf("applyPeriodicBoundary_double(%f, %f) = %f\n", prev_double, max_double, result_double);
    #endif

    #ifdef UNMATCH_TYPE_TEST
        int prev_int = -5;
        double max_double = 10.0;
        double result_double = applyPeriodicBoundary(prev_double, max_double);
        printf("applyPeriodicBoundary_double(%d, %f) = %f\n", prev_int, max_double, result_double);
    #endif

    return 0;
}
