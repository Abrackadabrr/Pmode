//
// Created by evgen on 21.10.2021.
//
#include<iostream>
#include<complex>
#include<vector>
#include<fstream>
#define v_type std::complex<double>

std::ostream& operator << (std::ostream& os, std::pair<v_type, double> a) {
    os << "{ " <<a.first << " " << a.second << " } ";
    return os;
}

v_type  function(v_type  x, double alpha, double hat_k) {
    return 1. - 1. / (x*x) - alpha * (1. / ((x - hat_k) * (x - hat_k)));
}
v_type derivative(v_type x,  double alpha, double hat_k) {
    return  2. / (x*x*x) + 2. * alpha / ((x - hat_k) * (x - hat_k) * (x - hat_k));
}

v_type f_text(v_type x) {
    return pow(x,3) - 1.;
}
v_type d_text(v_type x) {
    return  3.*pow(x,2);
}

template<typename funk_type>
v_type next_step(funk_type function, funk_type derivative, v_type x_n, double alpha, double hat_k){
    return x_n - (function(x_n, alpha, hat_k))/(derivative(x_n, alpha, hat_k));
}

template<typename func_type>
std::vector<v_type> newton_method(func_type function, func_type derivative, double precise, v_type x_start, double alpha, double hat_k) {
    v_type x_n = next_step(function, derivative, x_start, alpha, hat_k);
    double measure_of_aggression = std::abs(x_start - x_n);
    std::vector<v_type> approximations;
    approximations.reserve(10000);
    approximations.emplace_back(x_n);
    while (measure_of_aggression > precise) {
        x_n = next_step(function, derivative, x_n, alpha, hat_k);
        measure_of_aggression = std::abs(x_n - *approximations.rbegin());
        approximations.emplace_back(x_n);
    }
    return approximations;
}

int main()
{
    double step_grid = 0.01;
    double precise = 0.00001;
    std::vector<double> alpha_vec{0.0001, 0.001, 0.01, 0.1, 0.99};
    for (auto alpha : alpha_vec){
        for (double hat_k = 0; hat_k < 7; hat_k+=0.05) {
            std::ofstream file("alpha_" + std::to_string(alpha) + "k_" +std::to_string(hat_k)+ + "_.txt");
            for (int i = -100; i < 100; i++)
                for (int j = -100; j < 100; j++) {
                    auto start_point = std::complex<double>(0.0 + i * step_grid, 0.0 + j * step_grid);
                    auto result = newton_method(function, derivative, precise, start_point, alpha, hat_k);
                    //               auto result = newton_method(f_text, d_text, 0.0001, start_point);
                    std::cout.precision(5);
                    if ((start_point.real() != 0) && (start_point.imag() != 0))
                        file << result.rbegin()->real() << " " << result.rbegin()->imag() << " " << result.size() << " "\
 << start_point.real() << " " << start_point.imag() << " " << alpha << " " << hat_k << std::endl;

                }
            std::cout << "k = " << hat_k << std::endl;
        }
            std::cout << alpha << std::endl;
    }
    return 0;
}
