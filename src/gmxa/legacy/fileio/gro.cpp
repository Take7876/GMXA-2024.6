#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/format.hpp>
#include "gmxa/fileio/gro.hpp"

#define max_atomidnum 99999
#define coord_rownum 44
#define velocity_rownum 68

int Gro::renumber(int atomid, int linenum){

    if(linenum < max_atomidnum && atomid != linenum) return false;
    else if(linenum > max_atomidnum) int atomid = linenum;
    return atomid;
}

bool Gro::check_velocity(std::string line){

    if(line.size() > coord_rownum && line.size() == velocity_rownum) return true;
    else return false;
}

bool Gro::check_coord(std::string line){

    if(line.size() < (coord_rownum - 1)) return false;
    else return true;   
}

int Gro::check_atomnum(std::string filename){
    
    std::ifstream inputfile(filename);
    std::string line;
    std::getline(inputfile, line);
    std::getline(inputfile, line);
    int linenum;
    for(int linenum = 0;;linenum ++){
        std::getline(inputfile, line);
        if(!Gro::getline(line)) break;
        else continue;   
    }
    inputfile.close();
    return linenum;
}

bool Gro::getline(std::string &line){

    if(line.empty()) return false;
    if(!Gro::check_coord(line)) return false;
    this->resid = stoi(line.substr(0,5));
    this->resname = line.substr(5,5);
    this->atomname = line.substr(10,5);
    this->atomid = stoi(line.substr(15,5));
    this->x = stod(line.substr(20,8));
    this->y = stod(line.substr(28,8));
    this->z = stod(line.substr(36,8));
    if(Gro::check_velocity(line)){
        this->velx = stod(line.substr(44,8));
        this->vely = stod(line.substr(52,8));
        this->velz = stod(line.substr(60,8));
    }

    return true;
}

#ifdef debug
bool Gro::getStep(std::string &filename){

    std::ifstream instanceGro(filename);
    std::string title, atomnumStr, line;
    std::getline(instanceGro, title);
    title.clear();
    std::getline(instanceGro, atomnumStr);
    int atomnum = std::stoi(atomnumStr);
    atomnumStr.clear();
    for(int i = 0; i < atomnum; i++){
        Gro grofile;
        std::getline(instanceGro, line);
        grofile.getline(line);
        this->resid.push_back(grofile.resid);
        this->resname.push_back(grofile.resname);
        this->atomname.push_back(grofile.atomname);
        this->atomid.push_back(grofile.atomid);
    }
    instanceGro.close();
    return true;
}
#endif


std::string Gro::setline(){
    std::string line = boost::str(boost::format("%5d%-5s%5s%5d%8.3lf%8.3lf%8.3lf")%this->resid%this->resname%this->atomname%this->atomid%this->x%this->y%this->z);
    std::cout << line << std::endl;
    return line;
}
