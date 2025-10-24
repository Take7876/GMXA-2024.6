#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ios>
#include <iomanip>

#include "opls/opls.hpp"
#include "opls/ffnonbonded.hpp"
#include "opls/aminoacid.hpp"
#include "opls/atomtype.hpp"
#include "opls/define.h"

#ifdef debug
void check_charge_opls(std::string &fname_aminoacids, std::string &fname_ffnonbonded, std::string &fname_atomtypes, const std::vector <std::string> &check_resname){
    /******************************************************************************************************/
    std::ifstream f_aminoacid(fname_aminoacids);
    if(!f_aminoacid.is_open()){
        std::cout << " file open error : " << fname_aminoacids << std::endl;
        return;
    }
    std::ifstream f_ffnonbonded(fname_ffnonbonded);
    if(!f_ffnonbonded.is_open()){
        std::cout << " file open error : " << fname_ffnonbonded << std::endl;
        return;
    }
    /******************************************************************************************************/
    for(int i = 0; i < check_resname.size(); i++){
        std::string line, temp_opls_id, temp_atomname;
        std::string target_resname = "[ " + check_resname[i] + " ]";
        std::vector <std::string> opls_id, atomname;
        std::vector <double> charge;
        double temp_charge, total_charge = 0.0;
        std::cout << "\n";
        for(int j = 0;; j++){
            std::getline(f_aminoacid, line);
            if(line.find(target_resname) != std::string::npos){
                for(int k = 0;; k++){
                    std::getline(f_aminoacid, line);
                    if(line.find("[ atoms ]") != std::string::npos) break;
                }
                for(int k = 0;; k++){
                    std::getline(f_aminoacid, line);
                    std::istringstream opls_list(line);
                    if(line.empty()) continue;
                    else if(line.find("[ bonds ]") != std::string::npos) break;
                    else if(opls_list >> temp_atomname >> temp_opls_id >> temp_charge){
                        total_charge  += temp_charge;
                        atomname.push_back(temp_atomname);
                        opls_id.push_back(temp_opls_id);
                        charge.push_back(temp_charge);
                    }
                    else std::cout << RED_TEXT << " error   : " << target_resname << " " << line << " has no charge" << RESET_TEXT << std::endl;
                }
                for(int k = 0; k < opls_id.size(); k++){
                    std::string name, bond_type, list_opls_id;
                    if(k >= 1000000){
                        std::cout << RED_TEXT << "warning : please increase number of setw()" << RESET_TEXT << std::endl;
                        break;
                    }
                    double mass;
                    for(int l = 0;; l++){
                        std::getline(f_ffnonbonded, line);
                        if(line.find(opls_id[k]) != std::string::npos){
                            std::string comment = At::search_comment(fname_atomtypes, opls_id, k);
                            std::istringstream read_line(line);
                            read_line >> list_opls_id >> name >> bond_type >> mass >> temp_charge; 
                            if(charge[k] != temp_charge){
                                std::cout << RED_TEXT << " error   : " << target_resname << std::right << std::setw(6) << k + 1 << std::right << std::setw(6) << atomname[k] << "\t"<< opls_id[k] << RESET_TEXT;
                                std::cout << RED_TEXT << "\t" << name  << "\t" << std::right << std::setw(7) << charge[k] << RESET_TEXT;
                                std::cout << "     " << "right charge : " << std::right << std::setw(7) << temp_charge << "\t;" << comment << std::endl;
                                break;
                            }
                            else if(charge[k] == temp_charge){
                                std::cout << " success : " << target_resname << std::right << std::setw(6) << k + 1 << std::right << std::setw(6) << atomname[k] << "\t" << opls_id[k];
                                std::cout << "\t" << name << "\t" << std::right << std::setw(7) << charge[k] << "\t;" << comment << std::endl;
                                break;
                            }
                        }
                        else if(f_ffnonbonded.eof()){
                            std::cout << "no such opls-ID in" << fname_ffnonbonded << "\t: /" << opls_id[k] << "/" << std::endl;
                            break;
                        };
                    }
                    f_ffnonbonded.clear();
                    f_ffnonbonded.seekg(0, std::ios::beg);
                }
                break;
            }
            else if(f_aminoacid.eof()){
                std::cout << RED_TEXT << "no such resname in " << fname_aminoacids << " : " << check_resname[i] << RESET_TEXT << std::endl;
                break;
            }
        }
        std::cout << TOTAL_END_LINE << std::endl;
        if(total_charge == 0.0) std::cout << " total charge in " << fname_aminoacids << " :\t" << total_charge << std::endl;
        else if(total_charge != 0.0) std::cout << " total charge in " << fname_aminoacids << " :\t" << RED_TEXT << total_charge << RESET_TEXT <<std::endl;
        std::cout << END_LINE << std::endl;
        f_aminoacid.clear();
        f_aminoacid.seekg(0, std::ios::beg);
    }
    f_aminoacid.close();
    f_ffnonbonded.close();
    /************************************************************************************************************/
    return;
}



void search_oplsid(std::string &fname_ffnonbonded, std::string &fname_atomtypes, std::vector <std::string> &check_oplsid){


    return;
}
#endif