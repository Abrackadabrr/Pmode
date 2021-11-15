#ifndef STRUCTURED_CODE_DESSIPATEPENDULUM_H
#define STRUCTURED_CODE_DESSIPATEPENDULUM_H

namespace PhysicalModels {
    /*
     * This class tris to model 2 order ODE describes math pendulum dissipation
     * Make sure that std::vector state accurately have four parameters
     * That is [angle, it's derivative, current_time, time_step], but functions don't really depend on current_time
     */
    template<typename value_t>
    class DissipatePeriodicPotential {
    private:
        value_t omega;
        value_t decrement;
        class VectorFunction {
        private:
            value_t omega;
            value_t decrement;

            value_t psiFunction(std::vector<value_t> &state, value_t time) const {
                value_t delta = 0;
                if (std::abs(time - 10.) < 0.00001) {delta = 500;}
                return -(2* decrement*state[1] + omega * std::sin(state[0])) + delta;
            }

            value_t xiFunction(std::vector<value_t> &state, value_t time) const {
                return state[1];
            }

        public:
            VectorFunction(value_t om, value_t decr) : omega(om), decrement(decr) {};

            std::vector<value_t> operator()(std::vector<value_t> &n_state, value_t time) const {
                return std::vector<value_t>{xiFunction(n_state, time), psiFunction(n_state, time)};
            }
        };

    public:
        DissipatePeriodicPotential(value_t omeg, value_t decr): omega(omeg), decrement(decr) { };
        value_t getOmega() { return omega; };
        void setOmega(value_t omeg) { omega = omeg; };
        value_t getDecrement() { return decrement; };
        void setDecrement(value_t omeg) { decrement = omeg; };
        auto getVectorFunction() {return VectorFunction(omega, decrement);};
        value_t countEnergy(value_t current_angle,value_t current_velocity){
            value_t next_energy =  (current_velocity*current_velocity)/2 + (omega*(1 - std::cos(current_angle)));
            return next_energy;
        }
        void write_to_csv(const std::vector<std::vector<value_t>> &res, const std::vector<value_t> &energy,
                          const std::vector<value_t> &time){
            std::ofstream file("dissipate.csv");
            file << std::fixed;
            file << "Phi;Der;En;T;Om;Decr\n";
            printCsvFormat(file, res[0]);
            file <<';'<< energy[0] <<';' << time[0] << ';' << omega << ';' << decrement;
            file << '\n';
            for (int i = 1; i < res.size(); ++i) {
                printCsvFormat(file, res[i]);
                file <<';'<< energy[i] <<';' << time[i];
                file << '\n';
            }
        }
    };
}


#endif //STRUCTURED_CODE_DESSIPATEPENDULUM_H
