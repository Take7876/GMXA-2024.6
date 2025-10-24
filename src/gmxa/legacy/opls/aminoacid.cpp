#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "opls/opls.hpp"
#include "opls/aminoacid.hpp"

bool search_residue(std::vector <std::string> &check_resname){

    std::ifstream f_aminoacid(Opls::fname_aminoacid);
    if(!f_aminoacid.is_open()){
        Opls::file_error = "file open error " + Opls::fname_aminoacid;
        return false;
    }

    return true;
}