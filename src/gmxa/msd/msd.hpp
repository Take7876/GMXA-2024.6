#ifndef MSD_GMXA_HPP
#define MSD_GMXA_HPP

class MSD{
    protected:
        struct ResultSqd{
            double count_data = 0.0;
            double square_disp = 0.0;
        };
        ResultSqd calculate_square_disp(const std::vector<double> &coord, int i_t);

    private:
        double check_count_data(double count_data_x, double count_data_y);
        double check_count_data(double count_data_x, double count_data_y, double count_data_z);

    public:
        bool calculate_msd(const std::vector<double> &coord, double dt);
        bool calculate_msd(const std::vector<double> &coord_x, const std::vector<double> &coord_y, double dt);
        bool calculate_msd(const std::vector<double> &coord_x, const std::vector<double> &coord_y, const std::vector<double> &coord_z, double dt);
        std::vector<double> time;
        std::vector<double> msd;
};

#endif