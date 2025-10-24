/* This header file is intended for reading xtc files. */
/* Currently, it supports the gromacs 2021 version of xtc files*/
/* How to compile:  g++ -std=c++14 ___.cpp -lgromacs  -I home/taketoshi/src/GMXA/ -o ____.out -I /home/taketoshi/src/gromacs-2021.7/src/ -L/home/taketoshi/apl/gromacs-2021.7/lib64/ */

#ifndef XTC_GMXA_HPP
#define XTC_GMXA_HPP

#pragma once
#include "gromacs/fileio/xtcio.h"
#include "gmxa/fileio/gro.hpp"

class Xtc : public Gro{

    private:
        t_fileio*   xtcfp;
        std::string fnameGro;
        bool        getGro(std::string &filename);
        void        clear();

    public:
        Xtc(){
            this->step = 0;
            this->time = 0.0;
            this->atomnum = 0;
            this->xbox = 0.0;
            this->ybox = 0.0;
            this->zbox = 0.0;
	    this->errCmt = "There are no errors";
        }
        bool        openXtc(char* fnameXtc, char* fnameGro);
        bool        readXtc(int step);
        void        closeXtc();
        int         step, atomnum;
        double      time, xbox, ybox, zbox;
        std::vector<int> atomid, resid;
        std::vector<double> x, y, z;
        std::vector<std::string> resname, atomname;
        std::string errCmt;
};

#endif
