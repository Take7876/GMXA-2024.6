#ifndef AMINOACID_OPLS_HPP
#define AMINOACID_OPLS_HPP

#pragma once
#include "opls/opls.hpp"

class Aminoacid : public Opls{
    public:
        bool search_residue(std::vector <std::string> &check_resname);
        std::string <std::string> atomtype;
        std::string <std::string> oplsid;
        std::string <std::string> charge;
};

#endif