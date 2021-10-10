#include <bits/stdc++.h>
#include<random>
#include <chrono>
#include <random>
#include<vector>

using std::vector;
using namespace std;

float getRandomFloat(float min, float max){
    std::default_random_engine r;
    std::uniform_real_distribution<float> d(min, max);
    return d(r);
}

std::pair<float, float> kahanSumForTwoValue(float a, float b, float compensation)
{
    float sum = 0;
    float tmp = 0;
    if (b > a) {
        tmp = a - compensation;
        sum = b + tmp;
        compensation = (sum - b) - tmp;
    } else {    
        tmp = b - compensation;
        sum = a + tmp;
        compensation = (sum - a) - tmp;
    }
    return std::move(std::pair<float, float>{sum, compensation});
}
 
float kahanSum(vector<float> &fa)
{
    float sum = 0.0;

    float compensation = 0.0;
 
    for(double f : fa)
    {
        auto result = kahanSumForTwoValue(sum, f, compensation);
        sum = result.first;
        compensation = result.second;
    }
    return sum;
}

float sum(vector<float> &fa)
{
    float sum = 0.0;
 
    for(auto f : fa)
    {
        sum = sum + f;
    }
    return sum;
}

int main()
{   cout.precision(10000000);
    const unsigned n = 100000000;
    vector<float> no(n);
    for(int i = 0; i < n; i++)
    {
        no[i] = 0.1;
        // std::cout << no[i] << std::endl;
    }
  
    std::cout << "Normal sum: " << sum(no) << " \n";
    std::cout << "Kahan sum: " << kahanSum(no)<< std::endl;
    return 0;
}
