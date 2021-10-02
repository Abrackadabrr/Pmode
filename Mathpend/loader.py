import os as os
import numpy as np
import matplotlib.pyplot as plt
import argparse
import sys


def createParser ():
    parser = argparse.ArgumentParser()
    parser.add_argument('st_an', type=str, default=str(3.1415/6))
    parser.add_argument('st_vel', type=str, default="0")
    parser.add_argument('integrator', type=str)
    
    parser.add_argument('-stp', '--time_step', type=str, default="0.01")
    parser.add_argument('--q_omega', type=str, default="1")
    parser.add_argument('-st', '--save_temps', action='store_const', const=True, default=False)
    parser.add_argument('-ft', '--full_time', type=str, default="10")
    parser.add_argument('-dfrq','--discr_frq', type=str, default="100")

    return parser

 
if __name__ == '__main__':

    parser = createParser()
    namespace = parser.parse_args (sys.argv[1:]) 
    time_step = namespace.time_step
    full_time = namespace.full_time
    discr_frq = namespace.discr_frq

    with open("input.txt", 'w') as i:
        i.write(namespace.q_omega + "\n")
        i.write(namespace.st_an + "\n")
        i.write(namespace.st_vel + "\n")
        i.write(time_step + "\n")
        i.write(str(int(int(full_time)/float(time_step)))+"\n")
        i.write(namespace.discr_frq)
    if (namespace.integrator == "kahon"):
        os.system("g++ kahon_math_pendulum.cpp -o math_pendulum.out")
        os.system("./math_pendulum.out")
    else:
        os.system("g++ math_pendulum.cpp -o math_pendulum.out")
        os.system("./math_pendulum.out")

    with open("angle.txt") as an:
        angle = np.array([float(i) for i in an.readlines()])
    with open("velocity.txt") as vel:
        velocity = np.array([float(i) for i in vel.readlines()])
    with open("energy.txt") as en:
        energy = np.array([float(i) for i in en.readlines()])

    time = [float(time_step)*i*float(discr_frq) for i in range(len(angle))]

    rel_en_err = (np.array([energy[0]]*len(energy)) - energy)/(energy[0])
     
    plt.plot(time, angle)
    plt.title(f"Угол от времени;\n шаг по времени {time_step}")
    plt.show()
    plt.plot(time, velocity)
    plt.title(f"Производная угла от времени;\n шаг по времени {time_step}")
    plt.show()
    plt.plot(angle, velocity)
    plt.title(f"Фазовая плоскость;\n шаг по времени {time_step}")
    plt.show()
    plt.plot(time, 100*rel_en_err)
    plt.plot(time, (np.array([0]*len(energy))), color='red')
    plt.title(f"Относительная ошибка интеграла движения;\n шаг по времени {time_step}")
    plt.show()

    os.system("rm math_pendulum.out")
    os.system("rm input.txt")
    if not namespace.save_temps:
        os.system("rm velocity.txt")
        os.system("rm angle.txt")
        os.system("rm energy.txt")

 
