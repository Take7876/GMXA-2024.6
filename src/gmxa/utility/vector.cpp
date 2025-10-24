#include <iostream>
#include <vector>
#include "gmxa/utility/vector.hpp"

bool Vector::check_element(std::vector<std::vector<double> > &prev_vec){

    int line_size = Vector::line_size(prev_vec);
    int row_size = Vector::row_size(prev_vec, 0);
    for(int i = 0; i < line_size; i++){
        if(row_size == prev_vec[i].size()) continue;
        else if(row_size != prev_vec[i].size()) return false;
    }
    return true;
}

int Vector::line_size(std::vector<std::vector<double> > &prev_vec){

    int line_size = prev_vec.size();
    return line_size;
}

int Vector::row_size(std::vector<std::vector <double> > &prev_vec, int i){

    int row_size = prev_vec[i].size();
    return row_size;
}

bool Vector::trans(std::vector<std::vector<double> > &prev_vec){

    if(!Vector::check_element(prev_vec)) return false;
    int line_size = Vector::line_size(prev_vec);
    int row_size = Vector::row_size(prev_vec, 0);
    for(int i = 0; i < row_size; i++){
        std::vector<double> temp_vec;
        for(int j = 0; j < line_size; j++) temp_vec.push_back(prev_vec[j][i]);
        this->vector.push_back(temp_vec);
    }
    prev_vec.clear();
    return true;
}
