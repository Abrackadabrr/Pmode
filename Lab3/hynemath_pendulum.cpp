#include<iostream>
#include<vector>
#include<array>
#include<fstream>
#include<istream>
#include<cmath>
using std::stof;

struct Con{
    float q_omega;
    float start_angel;
    float start_velocity;
    float time_step;
};

std::array<float,3> next_step(float current_angle, float current_velocity, Con constants)
{
    float eiler_next_velocity = current_velocity - constants.q_omega * std::sin(current_angle) * constants.time_step;
    float eiler_next_angle = current_angle + current_velocity * constants.time_step;
   
    float next_velocity = current_velocity - constants.q_omega * std::sin(eiler_next_angle) * constants.time_step;
    float next_angle = current_angle + eiler_next_velocity * constants.time_step;

    float hyne_velocity = (eiler_next_velocity + next_velocity) / 2.f;
    float hyne_angle = (eiler_next_angle + next_angle) / 2.f;
 
    float next_energy =  (current_velocity*current_velocity)/2 + (constants.q_omega*(1 - std::cos(current_angle)));
    return (std::array<float, 3>{hyne_angle, hyne_velocity, next_energy});
}

std::array<std::vector<float>, 3> calculate(Con constants,int full_iters)
{
    std::vector<float> angles;
    angles.reserve(full_iters);
    angles.push_back(constants.start_angel);
    std::vector<float> velocity;
    velocity.push_back(constants.start_velocity);
    std::vector<float> energy;
    energy.push_back((*velocity.rbegin())*(*velocity.rbegin())/2 + (constants.q_omega*(1-std::cos(*angles.rbegin()))));

    for(int i = 0; i < full_iters; ++i) {
        auto next_step1 = next_step(*angles.rbegin(), *velocity.rbegin(), constants);
        angles.push_back(next_step1[0]);
        velocity.push_back(next_step1[1]);
        energy.push_back(next_step1[2]);
    } 
    return std::array<std::vector<float>, 3>{std::move(angles), std::move(velocity), std::move(energy)};
}

int main()
{
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
