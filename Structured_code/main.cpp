#include<iostream>
#include <vector>
#include "Eiler.h"
#include "vectrors.h"
#include "PeriodicPotential.h"
#include "DessipatePendulum.h"


int main() {
    PhysicalModels::PeriodicPotential model(1);
    PhysicalModels::DissipatePeriodicPotential model2(1, 1);
    std::vector<double> state{0, 1, 0, 0.001};
    std::cout << state << std::endl;
    auto res = ODE_Solvers::eiler_method(model.getVectorFunction(), state, 10);
    return 0;
}
