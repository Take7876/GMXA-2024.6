#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "gromacs/fileio/xtcio.h"
#include "gmxa/fileio/gro.hpp"
#include "gmxa/fileio/xtc.hpp"

bool Xtc::openXtc(char* fnameXtc, char* fnameGro){

    t_fileio* fio;
    fio = open_xtc(fnameXtc,"r");
    this->xtcfp = fio;
    this->fnameGro = std::string(fnameGro);
    return true;
}

void Xtc::closeXtc(){
    close_xtc(this->xtcfp);
    return;
}

bool Xtc::readXtc(int targetStep){

    this->clear();
    int natoms;
    int64_t step;
    real time;
    real prec;
    matrix box;
    rvec *x;
    gmx_bool bOK;

    int checkFirst = read_first_xtc(this->xtcfp, &natoms, &step, &time, box, &x, &prec, &bOK);
    if(checkFirst == 0){
        this->errCmt = "Error at first step in xtcfile";
        return false;
    }

    if(targetStep == int(step)){
        this->time = (double)time;
        this->step = (int)step;
        this->atomnum = natoms;
        this->xbox = box[0][0];
        this->ybox = box[1][1];
        this->zbox = box[2][2];
        for(int i = 0; i < natoms; i++){
            this->x.push_back(x[i][0]);
            this->y.push_back(x[i][1]);
            this->z.push_back(x[i][2]);
        }
        if(!this->getGro(this->fnameGro)){
            this->errCmt = "Error at grofile \nprogram name is gro.cpp";
            return false;
        }
        return true;
    }

    for(int i = 0;; i ++){
        int checkNext = read_next_xtc(this->xtcfp, natoms, &step, &time, box, x, &prec, &bOK);
        if(checkNext == 0){
            this->errCmt = "Error at " + std::to_string(step) + " step in xtcfile";
            return false;
        }
        else if(targetStep == (int)step){
           this->time = (double)time;
            this->step = (int)step;
            this->atomnum = natoms;
            this->xbox = box[0][0];
            this->ybox = box[1][1];
            this->zbox = box[2][2];            
            for(int i = 0; i < natoms; i++){
                this->x.push_back(x[i][0]);
                this->y.push_back(x[i][1]);
                this->z.push_back(x[i][2]);
            }
            if(!this->getGro(this->fnameGro)){
                this->errCmt = "Error at grofile \nprogram name is gro.cpp";
                return false;
            }  
            return true;
        }
    }

    if(this->atomnum != this->atomid.size()){
        this->errCmt = "The number of atoms in the gro file and the number of atoms in the xtc file do not match";
        return false;
    }

    this->errCmt = "no such step number in xtcfile";
    return false;
}

bool Xtc::getGro(std::string &filename){

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

void Xtc::clear(){
    this->atomid.clear();
    this->atomname.clear();
    this->resid.clear();
    this->resname.clear();
    this->x.clear();
    this->y.clear();
    this->z.clear();
    return;
}
