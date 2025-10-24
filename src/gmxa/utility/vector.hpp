#ifndef VEC_GMXA_HPP
#define VEC_GMXA_HPP

class Vector{
    private:
        bool check_element(std::vector<std::vector<double> > &prev_vec);

    public:
        std::vector<std::vector<double> > vector;
        bool trans(std::vector<std::vector<double> > &prev_vec);
        int line_size(std::vector<std::vector<double> > &prev_vec);
        int row_size(std::vector<std::vector<double> > &prev_vec, int i);
};

#endif
