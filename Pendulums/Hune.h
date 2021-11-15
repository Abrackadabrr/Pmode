#include<iostream>

namespace ODE_Solvers {
    /*
     * Sub-function for predict_correct_method
     * Make only one step in this method
     * Make sure that arguments of vector_function is exactly std::vector<value_t> and time
     */
    template<typename value_t, typename vector_function>
    std::vector<value_t> hune_next_step(const vector_function& func, std::vector<value_t>& state, value_t time, value_t timestep) {
#if 1
        auto current_state = state;
        state = ODE_Solvers::eiler_next_step(func, state, time, timestep);
        return std::move(((current_state + func(state, time)*timestep) + state)*static_cast<value_t>(0.5));
#endif
        //return std::move((eiler_next_step(func, state, time, timestep) + predict_correct_next_step(func, state, time, timestep))*static_cast<value_t>(0.5));
    }

    /*
     * Based on hune_next_method
     * Make n_iters iterations of method
     * Make sure that arguments of vector_function is exactly std::vector<value_t> and time
     * initial_state is initial state of a system
     */
    template<typename value_t, typename vector_function>
    std::vector<std::vector<value_t>> hune_method(vector_function func, const std::vector<value_t>& initial_state,
                                                             value_t initial_time, value_t timestep, int n_iters) {
        std::vector<std::vector<value_t>> result;
        result.reserve(n_iters);

        auto state = initial_state;
        value_t time = initial_time;
        result.push_back(state);
        for (int i = 0; i < n_iters; ++i) {
            state = ODE_Solvers::hune_next_step(func, state, time, timestep);
            time += timestep;
            result.push_back(state);
        }
        return std::move(result);
    }
}