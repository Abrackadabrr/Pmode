//
// Created by evgen on 23.10.2021.
//

#ifndef DISPERSION_NEWTON_H
#define DISPERSION_NEWTON_H
#include <optional>

namespace Equation_Solvers {

    /*
     * Function checked value_type broken
     */
    template<typename value_type>
    bool is_broken(value_type x){
        if (std::isnan(x) || std::isinf(x))
            return true;
        return false;
    }
    bool is_broken(std::complex<double> x){
        if (std::isnan(x.real())||std::isnan(x.imag())|| std::isinf(x.real()) || std::isinf(x.imag()))
            return true;
        return false;
    }

    /*
     * Sub_function for Newton method
     */
    template<typename func_type,  typename  derivative_type, typename value_type>
    value_type Newton_next_step(func_type function, derivative_type derivative, value_type x_n) {
        return  x_n - (function(x_n)) / (derivative(x_n));
    }

    /*
     * Returns std::optional<std::vector<v_type>> with sequence of approximation
     * and last of its is with relative error below tolerance
     *
     * function and derivative is functions with itself environment including in its instance
     *
     * x_start is start approximation
     */
    template<typename func_type, typename  derivative_type, typename value_type>
    std::optional<std::vector <value_type>>
    newton_method(func_type function, derivative_type derivative, value_type x_start, double tolerance) {

        const int ITERATION_TOLERANCE = 1000;
        int counter_of_iterations  = 0;

        value_type x_n = Newton_next_step(function, derivative, x_start);
        if (is_broken(x_n)) return { };

        double measure_of_aggression = std::abs(x_start - x_n);

        std::vector <value_type> approximation_sequence;
        approximation_sequence.reserve(ITERATION_TOLERANCE);
        approximation_sequence.emplace_back(x_n);

        while (measure_of_aggression > tolerance) {

            x_n = Newton_next_step(function, derivative, x_n);
            if (is_broken(x_n))  return { };
            if (counter_of_iterations > ITERATION_TOLERANCE) return { };

            measure_of_aggression = std::abs(x_n - *approximation_sequence.rbegin());
            counter_of_iterations++;

            approximation_sequence.emplace_back(x_n);
        }
        return approximation_sequence;
    }
}

#endif //DISPERSION_NEWTON_H
