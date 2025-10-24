#include <iostream>
#include "gromacs/fileio/xtcio.h"

int main (int argc, char** argv){

    t_fileio* fio = open_xtc(argv[1], "r");

    int natoms;
    int64_t step;
    real time;
    real prec;
    matrix box;
    rvec *x;
    gmx_bool bOK;

    int check_first = read_first_xtc(fio, &natoms, &step, &time, box, &x, &prec, &bOK);
    std::cout << "Time: " << time << std::endl;;
    std::cout << "Step: " << step << std::endl;
    std::cout << "Prec: " << prec << std::endl;;
    std::cout << "boxx: " << box[0][0] << std::endl;
    std::cout << "boxy: " << box[1][1] << std::endl;
    std::cout << "boxz: " << box[2][2] << std::endl;
    std::cout << x[0][0] << "\t" << x[0][1] << "\t" << x[0][2] << std::endl;

    for(int j = 0;; j ++){
        int check_next = read_next_xtc(fio, natoms, &step, &time, box, x, &prec, &bOK);
        if(check_next == 0) break;
        std::cout << "Time: " << time << std::endl;;
        std::cout << "Step: " << step << std::endl;
        std::cout << "Prec: " << prec << std::endl;;
        std::cout << "boxx: " << box[0][0] << std::endl;
        std::cout << "boxy: " << box[1][1] << std::endl;
        std::cout << "boxz: " << box[2][2] << std::endl;
        std::cout << x[0][0] << "\t" << x[0][1] << "\t" << x[0][2] << std::endl;
    }
    //for(int i = 0; i < natoms; i++){
    //    std::cout << x[i][0] << "\t" << x[i][1] << "\t" << x[i][2] << std::endl;
    //}

    close_xtc(fio);
    return 0;
}
