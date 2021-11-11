#ifndef STRUCTURED_CODE_PERIODICPOTENTIAL_H
#define STRUCTURED_CODE_PERIODICPOTENTIAL_H
#include <cmath>

namespace PhysicalModels {

    /*
     * This class tris to model 2 order ODE describes ideal math pendulum
     * Make sure that std::vector state accurately have four parameters
     * That is [angle, it's derivative, current_time, time_step], but functions don't really depend on current_time
     */
    class PeriodicPotential {
    private:
        double omega;

        class VectorFunction {
        private:
            double omega;

            double psiFunction(std::vector<double> &state) const {
                return state[1] - omega * std::sin(state[0]) * state[3];
            }

            double xiFunction(std::vector<double> &state) const {
                return state[0] + state[1] * state[3];
            }

        public:
            VectorFunction(double om) : omega(om) {};

            std::vector<double> operator()(std::vector<double> &n_state) const {
                return std::vector<double>{xiFunction(n_state), psiFunction(n_state), n_state[2], n_state[3]};
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
