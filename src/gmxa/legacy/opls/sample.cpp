#include <iostream>
#include <string>
#include <vector>
#include "opls/opls.hpp"
#include "opls/atomtype.hpp"

int main(void){
    std::vector <std::string> opls_data;
    opls_data.push_back("opls_145");
    opls_data.push_back("opls_146");
    opls_data.push_back("opls_255");

    Atomtype atomtype;
    atomtype.fname_atomtypes = "sample/atomtypes.atp";
    for(int i = 0; i < opls_data.size(); i++){
        std::cout << opls_data[i] << std::endl;
        if(atomtype.getOplsid(opls_data[i])){
            std::cout << atomtype.setResult() << std::endl;
        }
        else{
            std::cout << "error" <<  std::endl;
            return 0;
        }
        
    }
    return 0;
}