#ifndef STRUCTURED_CODE_PERIODICPOTENTIAL_H
#define STRUCTURED_CODE_PERIODICPOTENTIAL_H
#include <cmath>

namespace PhysicalModels {

    /*
     * This class tris to model 2 order ODE describes ideal math pendulum
     * Make sure that std::vector state accurately have four parameters
     * That is [angle, it's derivative], but functions don't really depend on current_time
     */
    class PeriodicPotential {
    private:
        double omega;

        class VectorFunction {
        private:
            double omega;

            double psiFunction(std::vector<double> &state) const {
                return (-omega * std::sin(state[0]));
            }

            double xiFunction(std::vector<double> &state) const {
                return state[1];
            }

        public:
            VectorFunction(double om) : omega(om) {};

            std::vector<double> operator()(std::vector<double> &n_state, double time) const {
                return std::vector<double>{xiFunction(n_state), psiFunction(n_state)};
            }
        };

    public:
        PeriodicPotential(double omeg) : omega(omeg) {};

        double getOmega() { return omega; };

        void setOmega(double omeg) { omega = omeg; };

         auto getVectorFunction() { return VectorFunction(omega); };
    };
}
#endif //STRUCTURED_CODE_PERIODICPOTENTIAL_H
