//
// Created by evgen on 21.10.2021.
//
#include<iostream>
#include<complex>
#include<vector>
#include<fstream>
#include "Newton.h"
#include "DispersionEquation.h"

/*
 * Return sequence of instance between start ans stop with step between each neighboring elements
 */
template<typename value_type>
std::vector<value_type> sequence(value_type start, value_type stop, value_type step)
{
    std::vector<value_type> result;
    result.reserve(static_cast<int>((stop - start)/step));
    for (int i = 0, stop_int = static_cast<int>((stop - start)/step); i < stop_int; ++i) {
        result.emplace_back(static_cast<value_type>(start + i * step));
    }
    return std::move(result);
}

std::ofstream &operator << (std::ofstream &os, std::vector<double>& v)
{
    for(auto i: v) {os << i <<' ';};
    return os;
}

int main()
{
    PhysicalModels::DispersionEquation<std::complex<double>> main_equation(0, 0);

    double step_grid = 0.01;
    double tolerance = 0.0000001;
    std::vector<double> alpha_seq{0.001, 0.01, 0.05, 0.3, 0.7};
    for(auto i: alpha_seq) {std::cout  << i <<' ';};
    std::vector<double> hat_k_seq = sequence<double>(0, 6, 0.01);

    for (auto alpha : alpha_seq){
        std::vector<std::vector<double>> data;
        data.reserve(100*100);

        for (auto hat_k : hat_k_seq) {
            main_equation.setAlpha(alpha);
            main_equation.setHat_k(hat_k);
            data.emplace_back(std::initializer_list<double>{alpha, hat_k});
            try {
                for (int i = -50; i < 50; i++)
                    for (int j = -50; j < 50; j++) {
                        auto start_point = std::complex<double>(0.0 + i * step_grid, 0.0 + j * step_grid);
                        auto result = Equation_Solvers::newton_method
                                (main_equation.get_function(), main_equation.get_derivative(), start_point, tolerance);

                        if ((start_point.real() != 0) && (start_point.imag() != 0) && result)
                            data.emplace_back(
                                    std::initializer_list<double>{result->rbegin()->real(), result->rbegin()->imag(),
                                                                  static_cast<double>(result->size()),
                                                                  start_point.real(),
                                                                  start_point.imag()});
                    }
            } catch (...) { std::cout << "Crashes with " ;}
            std::cout << hat_k << '\n';
        }
        std::ofstream file("/media/evgen/Big_disc/MIPT/2nd level/Chapter 3/Pmode/Dispersion/Data3/"+ std::to_string(alpha) +".txt");
        if (file) {
            for (auto &i : data)
                file << i << '\n';
            std::cout << "asas" << '\n';
        }
    }
    return 0;
}
