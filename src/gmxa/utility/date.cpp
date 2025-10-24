#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "gmxa/utility/date.hpp"

void date(std::ostream &fobj){

    auto now = std::chrono::system_clock::now();
    
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm = *std::localtime(&now_c);

    fobj << "# Creation time : " << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") <<std::endl;

    return;
}
/* 2024.09.16
std::string date(){

    auto now = std::chrono::system_clock::now();
    
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}
*/
