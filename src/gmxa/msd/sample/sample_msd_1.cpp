#include <iostream>
#include <vector>
#include <array>
#include "msd/msd.hpp"

int main(void){
    std::vector <double> vec;
    vec.push_back(3.0);
    vec.push_back(6.0);
    vec.push_back(9.0);
    vec.push_back(5.0);
    vec.push_back(4.0);
    vec.push_back(3.0);
    vec.push_back(2.0);

    MSD msd;
    msd.calculate_msd(vec, 0.1);
    for(int i = 0; i < 7; i ++){
        std::cout << msd.time[i] << "\t" << msd.msd[i] << std::endl;
    }
    return 0;

}