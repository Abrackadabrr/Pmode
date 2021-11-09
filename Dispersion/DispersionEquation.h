//
// Created by evgen on 06.11.2021.
//

#ifndef DISPERSION_PERIODICPOTENTIAL_H
#define DISPERSION_PERIODICPOTENTIAL_H
namespace PhysicalModels {
    /*
     * Class modeling dimensionless dispersion equation with its left part and its first derivative
     */
    template<typename T>
    class DispersionEquation {
    private:
        double alpha;
        double hat_k;

        class function {
        private:
            double alpha;
            double hat_k;
        public:
            function(double alpha, double hat_k) : alpha(alpha), hat_k(hat_k) {}

            T operator()(T x) {
                return 1. - 1. / (x * x) - alpha * (1. / ((x - hat_k) * (x - hat_k)));
            }
        };

        class derivative {
        private:
            double alpha;
            double hat_k;
        public:
            derivative(double alpha, double hat_k) : alpha(alpha), hat_k(hat_k) {}

            T operator()(T x) {
                return 2. / (x * x * x) + 2. * alpha / ((x - hat_k) * (x - hat_k) * (x - hat_k));
            }
        };

    public:
        DispersionEquation(double alpha, double hat_k) {};

        auto get_function() const {
            return function(alpha, hat_k);
        }

        auto get_derivative() const {
            return derivative(alpha, hat_k);
        }

        void setAlpha(double alph) { alpha = alph; };

        void setHat_k(double alph) { hat_k = alph; };
    };
}
#endif //DISPERSION_PERIODICPOTENTIAL_H
