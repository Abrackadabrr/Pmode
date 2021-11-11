#ifndef STRUCTURED_CODE_DESSIPATEPENDULUM_H
#define STRUCTURED_CODE_DESSIPATEPENDULUM_H

namespace PhysicalModels {
    /*
     * This class tris to model 2 order ODE describes math pendulum dissipation
     * Make sure that std::vector state accurately have four parameters
     * That is [angle, it's derivative, current_time, time_step], but functions don't really depend on current_time
     */
    class DissipatePeriodicPotential {
    private:
        double omega;
        double decrement;
        class VectorFunction {
        private:
            double omega;
            double decrement;
            double psiFunction(std::vector<double> &state) const {
                return state[1] - (2* decrement*state[1] + omega * std::sin(state[0])) * state[3];
            }

            double xiFunction(std::vector<double> &state) const {
                return state[0] + state[1] * state[3];
            }

        public:
            VectorFunction(double om, double decr) : omega(om), decrement(decr) {};

            std::vector<double> operator()(std::vector<double> &n_state) const {
                return std::vector<double>{xiFunction(n_state), psiFunction(n_state), n_state[2], n_state[3]};
            }
        };

    public:
        DissipatePeriodicPotential(double omeg, double decr): omega(omeg), decrement(decr) { };
        double getOmega() { return omega; };
        void setOmega(double omeg) { omega = omeg; };
        double getDecrement() { return decrement; };
        void setDecrement(double omeg) { decrement = omeg; };
        auto getVectorFunction() {return VectorFunction(omega, decrement);};
    };
}


#endif //STRUCTURED_CODE_DESSIPATEPENDULUM_H
