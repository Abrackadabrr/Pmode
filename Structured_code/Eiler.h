#include<iostream>
#include <vector>
#include <numeric>
#include "vectrors.h"

namespace ODE_Solvers{
    /*
     * Sub-function for eiler_method
     * Make only one step in this method
     * Make sure that arguments of vector_function is exactly std::vector<value_t> and time
     */
    template<typename value_t, typename vector_function>
    std::vector<value_t> eiler_next_step(const vector_function& func, std::vector<value_t>& state, value_t time, value_t timestep) {
        return std::move(state + func(state, time)*timestep);
    }

    /*
     * Based on eiler_next_method
     * Make n_iters iterations of method
     * Make sure that arguments of vector_function is exactly std::vector<value_t> and time
     * initial_state is initial state of a system
     */
    template<typename value_t, typename vector_function>
    std::vector<std::vector<value_t>> eiler_method(vector_function func, const std::vector<value_t>& initial_state,
                                                    value_t initial_time, value_t timestep, int n_iters) {
        std::vector<std::vector<value_t>> result;
        result.reserve(n_iters);

        auto state = initial_state;
        value_t time = initial_time;
        result.push_back(state);
        for (int i = 0; i < n_iters; ++i) {
            state = ODE_Solvers::eiler_next_step(func, state, time, timestep);
            time += timestep;
            result.push_back(state);
        }
        return std::move(result);
    }
}
