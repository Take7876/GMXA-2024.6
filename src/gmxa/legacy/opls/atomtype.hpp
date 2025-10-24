#ifndef ATOMTYPE_OPLS_HPP
#define ATOMTYPE_OPLS_HPP

#pragma once
#include "opls/opls.hpp" 

class Atomtype : public Opls{
    private:
        bool search(const std::string &opls_id);  /* search for comment in atomtype.atp */
        std::string comment;
        std::string error;

    public:
        Atomtype(){
            Atomtype::comment.clear();
            Atomtype::error.clear();
        };
        bool getOplsid(const std::string &opls_id);
        std::string setResult();
};

#endif