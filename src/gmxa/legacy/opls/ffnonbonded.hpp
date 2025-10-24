#ifndef FFNONBONDED_OPLS_HPP
#define FFNONBONDED_OPLS_HPP

#pragma once
#include "opls/opls.hpp"

class FFnonbonded : public Opls{
    public:
        bool search(std::vector <std::string> &oplsid); /* search for atomtypes and charge in ffnonbonded*/
        std::vector <double> charge;
        std::vector <std::string> atomtype;
        std::string opls_error;  
        std::string charge_error;
        std::string atomtype_error; 
};

#endif