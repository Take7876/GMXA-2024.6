
/* This program is a sample. cannot compile */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "msd/msd.hpp"
#include "utility/vector.hpp"
#include "utility/gro.hpp"

int main(int argc, char *argv[]){

    std::string line;
    std::ifstream inputfile(argv[1]);
    std::vector<std::vector <double>> coord_x;
    std::vector<std::vector <double>> coord_y;
    std::vector<std::vector <double>> coord_z;
    for(int i = 0; !inputfile.eof(); i++){
        std::getline(inputfile, line);
        if(line.empty()) break;
        std::getline(inputfile, line);
        int atomnum = stoi(line);
        std::vector<double> temp_x;
        std::vector<double> temp_y;
        std::vector<double> temp_z;
        for(int j = 0; j < atomnum;  j++){
            std::getline(inputfile, line);
            Grofile grofile;
            if(!grofile.getline(line)) std::cout << "error" << std::endl;
	        if(grofile.atomid == 100 ){
            	temp_x.push_back(grofile.coord_x);
            	temp_y.push_back(grofile.coord_y);
            	temp_z.push_back(grofile.coord_z);
	        }		
        }
        std::getline(inputfile, line);
        coord_x.push_back(temp_x);
        coord_y.push_back(temp_y);
        coord_z.push_back(temp_z);
    }
    inputfile.close();
    Vector x, y, z;
    if(!x.trans(coord_x))std::cout << "error trans x" << std::endl;
    if(!y.trans(coord_y))std::cout << "error trans y" << std::endl;
    if(!z.trans(coord_z))std::cout << "error trans z" << std::endl;
    int stepnum = x.vector.size();
#ifndef debug
    MSD instance[stepnum];
    for(int i = 0; i < x.vector.size(); i++){
        if(!instance[i].calculate_msd(x.vector[i], y.vector[i], z.vector[i], 0.025)){
            std::cout << "error: msd" << std::endl;
            return -1;
        }
        for(int j = 0; j < instance[i].time.size(); j++) std::cout << instance[i].time[j] << "\t" << instance[i].msd[j] << std::endl;
    }
#endif
    return 0;
}
