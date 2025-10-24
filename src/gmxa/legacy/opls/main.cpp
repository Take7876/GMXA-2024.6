#include <iostream>
#include <string>
#include <vector>
#include "opls/opls.hpp"
#include "opls/define.h"

int main(int argc, char *argv[]){

    std::cout << "\n" << std::endl; 
    if(argc < 4){
        std::cout << RED_TEXT <<" error : The file name or number of files is insufficient" << RESET_TEXT << std::endl;
        std::cout << " argv[1] : Check file containing residue names to check (aminoacids.rtp)" << std::endl;
        std::cout << " argv[2] : Input file that you want to check opls id (ffnonbonded.itp)" << std::endl;
        std::cout << " argv[3] : Input file that you want to check atomtypes (atomtypes.atp)\n" << std::endl;
        return -1; 
    }
    std::string fname_aminoacids(argv[1]); 
    std::string fname_ffnonbonded(argv[2]);
    std::string fname_atomtypes(argv[3]);
 
    /* select resname you want to check charge ************************************************************/
    std::vector<std::string> check_resname;
    std::vector<std::string> check_opls_id;
    for(int i = 0;; i ++){
        if(i == 0){
            std::cout << "This is a program to check whether the opls charges are input correctly.\n" << std::endl;
            std::cout << "Please input resname you want to check." << std::endl;
            std::cout << "If you have finished entering the residue name, please select \"end\".\n" << std::endl;
            std::cout << "Your select resname : ";
            std::string search_str; 
            std::cin >> search_str;
            if(search_str == "end"){
                std::cout <<  " please input resname"  << std::endl; 
                return -1;
            }
            else if(search_str.find("opls_") == std::string::npos) check_resname.push_back(search_str); 
            else if(search_str.find("opls_") != std::string::npos) check_opls_id.push_back(search_str);
        }
        else if(i > 0){
            std::cout << "Your select resname : ";
            std::string search_str;
            std::cin >> search_str;
            if(search_str == "end") break;
            else if(search_str.find("opls_") == std::string::npos) check_resname.push_back(search_str); 
            else if(search_str.find("opls_") != std::string::npos) check_opls_id.push_back(search_str);
        }
    }
    std::cout << END_LINE << std::endl;
    /********************************************************************************************************/

    check_charge_opls(fname_aminoacids, fname_ffnonbonded, fname_atomtypes, check_resname);

    return 0;
}