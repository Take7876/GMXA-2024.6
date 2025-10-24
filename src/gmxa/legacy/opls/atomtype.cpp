#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "opls/opls.hpp"
#include "opls/atomtype.hpp"

bool Atomtype::getOplsid(const std::string &opls_id){

    if(Atomtype::search(opls_id)) return true;
    return false; 
};

bool Atomtype::search(const std::string &opls_id){
    
    std::ifstream f_atomtypes(Atomtype::fname_atomtypes);
    if(!f_atomtypes.is_open()){
        Atomtype::file_error = "file open error in " + Atomtype::fname_atomtypes;
        return true;
    }

    //Atomtype::comment.clear();
    Atomtype::error.clear();
    std::string default_comment = "No comments";
    std::string line, opls_id_str;
    Atomtype::comment = default_comment;
    for(int i = 0;; i++){
        std::getline(f_atomtypes, line);
        if(line[0] == ';') continue;
        else if(line.find(opls_id)!= std::string::npos){
            size_t mark_position = line.find_first_of(";");
            if(mark_position != std::string::npos){
                std::string first_line = line.substr(0, mark_position + 1);
                std::string last_line = line.substr(mark_position + 1);
                Atomtype::comment = last_line;
                if(Atomtype::comment.empty()){
                    Atomtype::error = "No comment at line " + std::to_string(i + i);
                    return true;
                }
                return true;
            }
            else{
                Atomtype::error = "ERROR at line " + std::to_string(i + i) + " : no such mark \";\".";
                return true;
            }
        }
        else if(f_atomtypes.eof()){
            std::string debug = "no such opld_id: " + opls_id + " in " + Atomtype::fname_atomtypes;
            Atomtype::error = debug;
            return true;
        }
        else continue;
    }
    f_atomtypes.close(); 
    if(Atomtype::comment == default_comment){
        Atomtype::error = "ERROR in atomtype.cpp";
        return true;
    }
    return false;
}

std::string Atomtype::setResult(){
    
    if(this->error.empty() && this->comment.empty()) return this->file_error;
    else if(this->error.empty() && !this->comment.empty()) return this->comment;
    else return this->error;
}