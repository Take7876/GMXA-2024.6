#ifndef GRO_GMXA_HPP
#define GRO_GMXA_HPP

#include <vector>

class Gro{

    private:
        bool    check_coord(std::string line);
        bool    check_velocity(std::string line);
        int     check_atomnum(std::string filename);

    public:
        int     atomid, resid;
        std::string atomname, resname;
        double  x, y, z, velx, vely, velz;
        bool    getline(std::string &line);
        //bool getstep(std::string &line);/*temp*/
        int     renumber(int atomid, int linenum); /*not compleate*/
        std::string setline();
};

#endif