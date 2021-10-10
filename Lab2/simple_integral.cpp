#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#include<fstream>
#include <vector>
#include <array>
#include "EbDawson.cpp"

class kahan_value{
private:
    float value;
    float compensation;

    static std::pair<float, float> kahanSumForTwoValue(float a, float b, float compen)
    {
        float sum = 0;
        float tmp = 0;
        if (b > a) {
            tmp = a - compen;
            sum = b + tmp;
            compen = (sum - b) - tmp;
        } else {
            tmp = b - compen;
            sum = a + tmp;
            compen = (sum - a) - tmp;
        }
        return std::move(std::pair<float, float>{sum, compen});
    }

public:
    kahan_value(float s): value(s), compensation(0) {};

    float getValue() {return value;};

    float getCompensation() {return compensation;};

    void add(float x)
    {
        auto result = kahanSumForTwoValue(value, x, compensation);
        value = result.first;
        compensation = result.second;
    };

    void setValue(float x) {value = x;};
};

float function(float x, float ksi)
{
    return std::exp((-1)*(x*x)/2.f) / (x - ksi);
}

float rectangle_integral_scheme(float starting_point, float end, float step, float ksi=0)
{
    kahan_value sum(0);
    kahan_value x(starting_point);

    for(int i = 0; x.getValue() < end; ++i) {
        float value = function(x.getValue(), ksi);
        sum.add(value*step);
        x.add(step);
    }
    return sum.getValue();
}


/*
 * Supposed that to - ksi = ksi - from
 */
float vp_rectangle_integral_scheme(float from, float to, float step, float ksi)
{
    kahan_value sum(0);
    kahan_value value(0);
    float precision = step;

    if (to < ksi || from > ksi) return rectangle_integral_scheme(from, to, step, ksi);
    else {
        sum.add(rectangle_integral_scheme(from, ksi-20, step, ksi));
        sum.add(rectangle_integral_scheme(ksi+20, to, step, ksi));
    }

    kahan_value x_left(ksi-10);
    kahan_value x_right(ksi+10);

    for(;x_right.getValue() > ksi+precision &&  x_left.getValue() < ksi-precision;) {
        value.setValue(0);
        value.add(function(x_left.getValue(), ksi));
        value.add(function(x_right.getValue(), ksi));
        sum.add(value.getValue() * step);

        x_left.add(step/10);
        x_right.add(-step/10);

#if 0
        std::cout << sum.getCompensation() << std::endl;
        std::cout << x_right.getCompensation() << std::endl;
        std::cout << x_left.getCompensation() << std::endl <<"\n";
#endif
    }
    return sum.getValue();
}

std::vector<std::array<float, 2>> mini_stupid_vp(float from, float to, float ksi_step, float precision_of_ksi, float integral_step){

    std::vector<std::array<float, 2>> res((int)((to-from)/ksi_step) + 10);
    float inf_precision = 100;
    for (float ksi = from; ksi < to; ksi += ksi_step) {
        float value = vp_rectangle_integral_scheme(-inf_precision, inf_precision, integral_step, ksi);
        res.push_back(std::array<float, 2>{ksi, value});
    }
    return std::move(res);
}

std::vector<std::array<float, 2>> stupid_vp(float from, float to, float ksi_step, float precision_of_ksi, float integral_step){

    std::vector<std::array<float, 2>> res((int)((to-from)/ksi_step) + 10);
    for (float ksi = from; ksi < to; ksi += ksi_step) {
        float inf_precision = 100;
        float value1 = rectangle_integral_scheme(-inf_precision, ksi - precision_of_ksi, integral_step, ksi);
        float value2 = rectangle_integral_scheme(ksi + precision_of_ksi, inf_precision, integral_step, ksi);
        res.push_back(std::array<float, 2>{ksi, value1+value2});
    }
    return std::move(res);
}

int main() {
    std::ofstream f("input.txt");

    const float ksi_step = 0.01;
    const float step = 0.001;
    const float epsilon = step;
    const float from = -3;
    const float to = 3;

    if (step > epsilon) {std::cout << "Down"; return 0;};

    auto graf_data = stupid_vp(from, to, ksi_step, epsilon, step);
    std::cout << std::boolalpha;
    std::cout.precision(100);
    for (auto i = graf_data.begin() + 100, end = graf_data.end();  i < end; ++i) f << (*i)[0] << " " << (*i)[1] <<  "\n";
    return 0;
}
