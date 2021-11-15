#ifndef STRUCTURED_CODE_PERIODICPOTENTIAL_H
#define STRUCTURED_CODE_PERIODICPOTENTIAL_H
#include <cmath>

namespace PhysicalModels {

    /*
     * This class tris to model 2 order ODE describes ideal math pendulum
     * Make sure that std::vector state accurately have four parameters
     * That is [angle, it's derivative], but functions don't really depend on current_time
     */
    template<typename value_t>
    class PeriodicPotential {
    private:
        value_t omega;

        class VectorFunction {
        private:
            value_t omega;

            value_t psiFunction(std::vector<value_t> &state) const {
                return (-omega * std::sin(state[0]));
            }

            value_t xiFunction(std::vector<value_t> &state) const {
                return state[1];
            }

        public:
            VectorFunction(value_t om) : omega(om) {};

            std::vector<value_t> operator()(std::vector<value_t> &n_state, value_t time) const {
                return std::vector<value_t>{xiFunction(n_state), psiFunction(n_state)};
            }
        };

    public:
        PeriodicPotential(value_t omeg) : omega(omeg) {};

        value_t getOmega() { return omega; };

        void setOmega(value_t omeg) { omega = omeg; };

         auto getVectorFunction() { return VectorFunction(omega); };

        value_t countEnergy(value_t current_angle,value_t current_velocity){
            value_t next_energy =  (current_velocity*current_velocity)/2 + (omega*(1 - std::cos(current_angle)));
            return next_energy;
        }
        void write_to_csv(const std::vector<std::vector<value_t>> &res, const std::vector<value_t> &energy,
                          const std::vector<value_t> &time){
            std::ofstream file("periodic.csv");
            file << std::fixed;
            file << "Phi;Der;En;T;Om\n";
            printCsvFormat(file, res[0]);
            file <<';'<< energy[0] <<';' << time[0] << ';' << omega;
            file << '\n';
            for (int i = 1; i < res.size(); ++i) {
                printCsvFormat(file, res[i]);
                file <<';'<< energy[i] <<';' << time[i];
                file << '\n';
            }
        }

    };
}
#endif //STRUCTURED_CODE_PERIODICPOTENTIAL_H
