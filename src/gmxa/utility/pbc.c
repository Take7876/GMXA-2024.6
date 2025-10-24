#include <stdio.h>
#include "gmxa/utility/pbc.h"


int applyPeriodicBoundary_int(int prev, int max){
    return (prev % max + max) % max;
}
double applyPeriodicBoundary_double(double prev, double max){
    
    int quotient = (int)(prev / max);
    double remainder = prev - (quotient * max);
    return remainder >= 0 ? remainder : (remainder + max);
}