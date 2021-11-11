#include<iostream>
#include <vector>
#include <numeric>
#include "vectrors.h"

namespace ODE_Solvers{
    /*
     * Sub-function for eiler_method
     * Make only one step in this method
     * Make sure that arguments of vector_function is exactly std::vector<value_t>
     */
    template<typename value_t, typename vector_function>
    std::vector<value_t> eiler_next_step(const vector_function& func, std::vector<value_t>& values) {
        return func(values);
    }

    /*
     * Based on eiler_next_method
     * Make n_iters iterations of method
     * Make sure that arguments of vector_function is exactly std::vector<value_t>
     * initial_state is initial state of a system
     */
    template<typename value_t, typename vector_function>
    std::vector<std::vector<value_t>> eiler_method(vector_function func, const std::vector<value_t>& initial_state, int n_iters){
        std::vector<std::vector<value_t>> result(initial_state.size());
        auto state = initial_state;
        for (auto param_sequnce_approximation: result)
            param_sequnce_approximation.reserve(n_iters);
        for (int i = 0; i < n_iters; ++i)
        {
            state = ODE_Solvers::eiler_next_step(func, state);
            state[state.size() - 2] += state[state.size() - 1];
            std::cout << state  << std::endl;
        }
        return result;
    }
}
