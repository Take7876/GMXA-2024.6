#include <iostream>
#include <vector>
#include <cmath>
#include "gmxa/msd/msd.hpp"

#define ERROR_CODE -1.0

MSD::ResultSqd MSD::calculate_square_disp(const std::vector<double> &coord, int i_t){

    ResultSqd result;
    int time_step = coord.size();
    double square_disp = 0.0;
    int count_data = 0;
    for(int i_t0 = 0;; i_t0++){
        if((i_t0 + i_t) >= time_step) break;
        square_disp += pow(coord.at(i_t0 + i_t) - coord.at(i_t0), 2);
        count_data ++;
    } 
    result.count_data = (double)count_data;
    result.square_disp = square_disp;

    return result;
}

bool MSD::calculate_msd(const std::vector<double> &coord, double dt){

    int time_step = coord.size();
    for(int i_t = 0; i_t < time_step; i_t++){
        double time = dt * (double)i_t;
        double msd_attime = 0.0;
        ResultSqd result = MSD::calculate_square_disp(coord, i_t);
        msd_attime = result.square_disp / result.count_data;
        this->time.push_back(time);
        this->msd.push_back(msd_attime);
    }
    return true;
}

double MSD::check_count_data(double count_data_x, double count_data_y){
    double count_data;
    if(count_data_x == count_data_y) count_data = count_data_x;
    else count_data = ERROR_CODE;
    return count_data;
}

bool MSD::calculate_msd(const std::vector<double> &coord_x, const std::vector<double> &coord_y, double dt){

    int time_step = coord_x.size();
    for(int i_t = 0; i_t < time_step; i_t ++){
        double time = dt * (double)i_t;
        double msd_attime = 0.0;
        ResultSqd result_x = MSD::calculate_square_disp(coord_x, i_t);
        msd_attime += result_x.square_disp;
        ResultSqd result_y = MSD::calculate_square_disp(coord_y, i_t);
        msd_attime += result_y.square_disp;
        double data_num = MSD::check_count_data(result_x.count_data, result_y.count_data);
        if(data_num == ERROR_CODE){
            msd_attime = ERROR_CODE;
            return false;
        }
        msd_attime = msd_attime / data_num;
        this->time.push_back(time);
        this->msd.push_back(msd_attime);
    }
    return true;
}

double MSD::check_count_data(double count_data_x, double count_data_y, double count_data_z){
    double count_data;
    if(count_data_x == count_data_y && count_data_x == count_data_z) count_data = count_data_x;
    else count_data = ERROR_CODE;
    return count_data;
}

bool MSD::calculate_msd(const std::vector<double> &coord_x, const std::vector<double> &coord_y, const std::vector<double> &coord_z, double dt){

    int time_step = coord_x.size();
    for(int i_t = 0; i_t < time_step; i_t ++){
        double time = dt * (double)i_t;
        double msd_attime = 0.0;
        ResultSqd result_x = MSD::calculate_square_disp(coord_x, i_t);
        msd_attime += result_x.square_disp;
        ResultSqd result_y = MSD::calculate_square_disp(coord_y, i_t);
        msd_attime += result_y.square_disp;
        ResultSqd result_z = MSD::calculate_square_disp(coord_z, i_t);
        msd_attime += result_z.square_disp;
        double data_num = MSD::check_count_data(result_x.count_data, result_y.count_data, result_z.count_data);
        if(data_num == ERROR_CODE){
            msd_attime = ERROR_CODE;
            return false;
        }
        msd_attime = msd_attime / data_num;        
        this->time.push_back(time);
        this->msd.push_back(msd_attime);
    }
    return true;    
}