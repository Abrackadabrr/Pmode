#include<iostream>
#include <vector>
#include "Eiler.h"
#include "PredictorCorrector.h"
#include "vectrors.h"
#include "PeriodicPotential.h"
#include "Hune.h"
#include "DessipatePendulum.h"

int main() {
    PhysicalModels::PeriodicPotential<double> model(1);
    double initial_time = 0.;
    double timestep = 0.001;
    int n_iters = 50000;
    std::vector<double> state{0, 0};

    auto res = ODE_Solvers::hune_method(model.getVectorFunction(), state, initial_time, timestep, n_iters);
    auto time = sequence(initial_time, double(n_iters+1)*timestep, timestep);
    std::vector<double> energy; energy.reserve(res.size());

    for (auto& i: res)
        energy.push_back(model.countEnergy(i[0], i[1]));

    model.write_to_csv(res, energy, time);
    return 0;
}
