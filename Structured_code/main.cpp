#include<iostream>
#include <vector>
#include <fstream>
#include "Eiler.h"
#include "vectrors.h"
#include "PeriodicPotential.h"
#include "DessipatePendulum.h"


int main() {

    PhysicalModels::DissipatePeriodicPotential model2(1, 0.05);
    double initial_time = 0.;
    double timestep = 0.001;
    int n_iters = 100000;
    std::vector<double> state{0.1, 0};
    auto res = ODE_Solvers::eiler_method(model2.getVectorFunction(), state, initial_time, timestep, n_iters);
    std::vector<double> energy; energy.reserve(res.size());
    for (auto& i: res)
        energy.push_back(model2.countEnergy(i[0], i[1]));


    std::ofstream file("periodic.txt");
    std::ofstream t("time.txt");
    std::ofstream e("energy.txt");
    std::ofstream p("params.txt");

    for (auto& i : res)
        file << i <<'\n';

    for (auto& i : energy)
        e << i <<'\n';

    for (auto& i : sequence(initial_time, (n_iters+1)*timestep, timestep))
        t << i <<'\n';

    p << model2.getOmega() << ' ' << model2.getDecrement();

    return 0;
}
