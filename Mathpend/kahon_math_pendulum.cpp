#include<iostream>
#include<vector>
#include<cmath>
#include<array>
#include<fstream>
#include<istream>

using std::stof;

struct Con{
    float q_omega;
    float start_angel;
    float start_velocity;
    float time_step;
};
/*
function KahanBabushkaNeumaierSum(input)
    var sum = 0.0
    var c = 0.0                       // A running compensation for lost low-order bits.

    for i = 1 to input.length do
        var t = sum + input[i]
        if |sum| >= |input[i]| then
            c += (sum - t) + input[i] // If sum is bigger, low-order digits of input[i] are lost.
        else
            c += (input[i] - t) + sum // Else low-order digits of sum are lost.
        endif
        sum = t
    next i

    return sum + c                    // Correction only applied once in the very end.
*/
std::pair<float, float> kahanSum(float b, float a, float compensation)
{   
    float sum = a;
    float c = 0.0;
    float t = sum + b;
    if (abs(sum) > abs(b)) c += (sum - t) + b;
    else c += (b - t) + sum;
    sum = t;
    /*
    float sum = 0;
    float tmp = 0;
    if (abs(b) >abs(a)) {
        tmp = a - compensation;
        sum = b + tmp;
        compensation = (sum - b) - tmp;
    } else {    
        tmp = b - compensation;
        sum = a + tmp;
        compensation = (sum - a) - tmp;
    }
    */
    return std::move(std::pair<float, float>{sum+c, c});
}

std::array<std::pair<float,float>,3> next_step(std::pair<float, float> current_angle, std::pair<float, float> current_velocity, float energy_comp, Con constants)
{
    auto next_velocity = kahanSum(current_velocity.first, (-1)*constants.q_omega * current_angle.first * constants.time_step, current_velocity.second);
    auto next_angle = kahanSum(current_angle.first, current_velocity.first * constants.time_step, current_angle.second);
    auto next_energy =  kahanSum((current_velocity.first*current_velocity.first)/2, (constants.q_omega*current_angle.first*current_angle.first/2), energy_comp);

   // std::cout << next_angle.second << "\t" << next_velocity.second << "\t" <<  next_energy.second << "\t" << std::endl;
    
    return std::move(std::array<std::pair<float,float>, 3>{next_angle, next_velocity, next_energy});
}


std::array<std::vector<float>, 3> calculate(Con constants,int full_iters)
{
    float angle_comp = 0.;
    float vel_comp = 0.;
    float energy_comp = 0.;    

    std::vector<float> angles;
    angles.push_back(constants.start_angel);

    std::vector<float> velocity;
    velocity.push_back(constants.start_velocity);

    std::vector<float> energy;
    energy.push_back((*velocity.rbegin())*(*velocity.rbegin())/2 + (constants.q_omega*(*angles.rbegin())*(*angles.rbegin())/2));


    for(int i = 0; i < full_iters; ++i) {
        auto next_step1 = next_step({*angles.rbegin(), angle_comp}, {*velocity.rbegin(), vel_comp}, energy_comp,  constants);

        angles.push_back(next_step1[0].first);
        velocity.push_back(next_step1[1].first);
        energy.push_back(next_step1[2].first);
        
        
        angle_comp = next_step1[0].second;
        vel_comp = next_step1[1].second;
        energy_comp = next_step1[2].second; 
    } 
    return std::move(std::array<std::vector<float>, 3>{std::move(angles), std::move(velocity), std::move(energy)});
}

int main()
{   
    std::cout << "I am kahon " << std::endl;    

    std::ofstream an("angle.txt");
    std::ofstream vel("velocity.txt");
    std::ofstream en("energy.txt");
    std::ifstream in("input.txt");
    std::string time_step, full_steps, discr_freq, start_angle, start_velocity, q_omega;
    if (in.is_open()){
        getline(in, q_omega);
        getline(in, start_angle);
        getline(in, start_velocity);
        getline(in, time_step);
        getline(in, full_steps);
        getline(in, discr_freq);
    }
    in.close(); 
    Con constants = {stof(q_omega),stof(start_angle), stof(start_velocity),stof(time_step)};

    auto data = calculate(constants, stoi(full_steps));

    int d_frq = std::stoi(discr_freq);

    int i = 0; 
    for(auto& as:data[0]) {
        if (i % d_frq == 0) 
            an << as << "\n";
        i++;
    }

    i = 0;
    for(auto& as: data[1]) {
        if (i % d_frq == 0)     
             vel << as << "\n";
        i++;
    }
    
    i = 0;
    for(auto& as: data[2]) {
         if (i % d_frq == 0)     
             en << as << "\n";
        i++;
    }
    return 0;
}
