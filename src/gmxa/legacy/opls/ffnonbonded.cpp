#include <iostream>
#include <vector>
#include <string>
#include "opls/opls.hpp"
#include "opls/ffnonbonded.hpp"
#include "opls/define.h"

std::stirng charge_sentence(){
    std::string comment;

    return comment;
}

bool search(std::vector <std::string> &oplsid){

    std::ifstream f_ffnonbonded(Opls::fname_ffnonbonded);
    if(!f_ffnonbonded.is_open()){
        Opls::file_error = "file open error " + Opls::fname_ffnonbonded;
        return false;
    }
    for(int i = 0; i < oplsid.size(); i++){
        std::string name, bond_type, list_oplsid, line;
        for(int j = 0;; j++){
            std::getline(f_ffnonbonded, line);
            if(line.find(opls_id[i]) != std::string::npos){
                double mass, temp_charge;
                std::istringstream readline(line);
                readline >> list_oplsid >> name >> bond_type >> mass >> temp_charge; 
                if(charge[k] != temp_charge){
                    std::string charge_error = charge_sentence();
                    std::cout << RED_TEXT << " error   : " << target_resname << std::right << std::setw(6) << k + 1 << std::right << std::setw(6) << atomname[k] << "\t"<< opls_id[k] << RESET_TEXT;
                    std::cout << RED_TEXT << "\t" << name  << "\t" << std::right << std::setw(7) << charge[k] << RESET_TEXT;
                    std::cout << "     " << "right charge : " << std::right << std::setw(7) << temp_charge;
                    break;
                }
                else if(charge[k] == temp_charge) break;
            }
            else if(f_ffnonbonded.eof()){
                FFnonbonded::opls_error = "no such opls-ID in" + Opls::fname_ffnonbonded + "\t: /" + opls_id[k] + "/";
                break;
            };
        }
        f_ffnonbonded.clear();
        f_ffnonbonded.seekg(0, std::ios::beg);
    }


    return true;
}