import os as os
import numpy as np
import matplotlib.pyplot as plt
import argparse
import sys


def createParser():
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

    # parser = createParser()
    # namespace = parser.parse_args(sys.argv[1:])
    # time_step = namespace.time_step
    # full_time = namespace.full_time
    # discr_frq = namespace.discr_frq
    # 
    # with open("input.txt", 'w') as i:
    #     i.write(namespace.q_omega + "\n")
    #     i.write(namespace.st_an + "\n")
    #     i.write(namespace.st_vel + "\n")
    #     i.write(time_step + "\n")
    #     i.write(str(int(int(full_time)/float(time_step)))+"\n")
    #     i.write(namespace.discr_frq)

    # os.system(f"g++ {namespace.integrator}math_pendulum.cpp -o math_pendulum.out")
    # os.system("./math_pendulum.out")

    with open("cmake-build-debug/periodic.txt") as an:
        data = np.array([np.array(list(map(float, i.split()))) for i in an.readlines()])
    with open("cmake-build-debug/time.txt") as t:
        time = np.array([float(i) for i in t.readlines()])
    with open("cmake-build-debug/energy.txt") as t:
        energy = np.array([float(i) for i in t.readlines()])
    with open("cmake-build-debug/params.txt") as t:
        omega, decr = map(float, t.read().split())

    time_step = time[1] - time[0]
    angle = data[:, 0]
    velocity = data[:, 1]

    fig, ax = plt.subplots(ncols=2, nrows=2)
    fig.suptitle(f"Шаг {time_step}, омега {omega}, декремент {decr}")

    ax[0][0].plot(time, angle)
    ax[0][0].set_title(f"Угол от времени")

    ax[1][0].plot(time, velocity)
    ax[1][0].set_title(f"Производная угла от времени")

    ax[0][1].plot(angle, velocity)
    ax[0][1].set_title(f"Фазовая плоскость")

    ax[1][1].plot(time, np.log(energy), label=f'k = {np.round(np.polyfit(time, np.log(energy), 1)[0], 4)}')
    # ax[1][1].plot(time, energy[0]*np.exp(np.polyfit(time, np.log(energy), 1)[0]*time))
    ax[1][1].set_title(f"Зависимость логарифма полной энергии системы от времени")
    ax[1][1].legend()
    
    for f in ax:
        for i in f:
            i.grid()

    plt.show()
