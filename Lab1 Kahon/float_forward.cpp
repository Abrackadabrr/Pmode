#include<iostream>
#include<cmath>
#include<array>
#include<numeric>
int main()
{
    std::cout.precision(30);
    float sum = 0;
    std::array<float, 200> a;
    for( auto& i:a ) {
        i = 0;
    } 
    unsigned long int i = 1; 
    while(i > 0) {
        for(auto sum = a.begin(), end = a.end(); sum < end; ++sum) {
            (*sum)= *sum + (float)1/i;
            i++;
        }
        for( auto& i:a ) {
            sum += i;
        } 
        std::cout << sum  << " " << i << std::endl;
        sum = 0;
    };
}
