import os as os
import numpy as np
import matplotlib.pyplot as plt
import argparse
import sys


def createParser():
    parser = argparse.ArgumentParser()
    parser.add_argument('st_an', type=str, default=str(3.1415 / 6))
    parser.add_argument('st_vel', type=str, default="0")
    parser.add_argument('integrator', type=str)

    parser.add_argument('-stp', '--time_step', type=str, default="0.01")
    parser.add_argument('--q_omega', type=str, default="1")
    parser.add_argument('-st', '--save_temps', action='store_const', const=True, default=False)
    parser.add_argument('-sf', '--save_fig', action='store_const', const=True, default=False)
    parser.add_argument('-ft', '--full_time', type=str, default="10")
    parser.add_argument('-dfrq', '--discr_frq', type=str, default="100")

    return parser


if __name__ == '__main__':

    fig, ax = plt.subplots()

    step_of_velocity = 0.00

    angles = np.array([])
    velocities = np.array([])

    parser = createParser()
    namespace = parser.parse_args(sys.argv[1:])
    time_step = namespace.time_step
    full_time = namespace.full_time
    discr_frq = namespace.discr_frq

    for step in range(1):
        with open("input.txt", 'w') as i:
            i.write(namespace.q_omega + "\n")
            i.write(namespace.st_an + "\n")
            i.write(str(float(namespace.st_vel) + step*step_of_velocity) + "\n")
            i.write(time_step + "\n")
            i.write(str(int(int(full_time) / float(time_step))) + "\n")
            i.write(namespace.discr_frq)

        os.system(f"g++ {namespace.integrator}math_pendulum.cpp -o math_pendulum.out")
        os.system("./math_pendulum.out")

        with open("angle.txt") as an:
            angle = np.array([float(i) for i in an.readlines()])
            np.delete(angle, 0)

        with open("velocity.txt") as vel:
            velocity = np.array([float(i) for i in vel.readlines()])
            np.delete(velocity, 0)

        time = [float(time_step) * i * float(discr_frq) for i in range(len(angle))]

        if not namespace.save_temps:
            os.system("rm velocity.txt")
            os.system("rm angle.txt")
            os.system("rm energy.txt")

        ax.plot(angle, velocity)
        ax.get_xaxis().set_label_text("Угол")
        ax.get_yaxis().set_label_text("Производная")

    fig.suptitle(f"{namespace.integrator.capitalize()} метод, Шаг по времени {time_step}, \nШаг по скорости {step_of_velocity}, Начальное значение {namespace.st_vel}")

    ax.grid()
    ax.set_aspect('equal')
    ax.set_yticks(np.arange(0, 3, 1))

    plt.show()

    if namespace.save_fig:
        plt.savefig(f"../pictures/Phase_trajectories/{namespace.integrator.capitalize()}_part2_boarder_case.png")

    os.system('rm math_pendulum.out')
    os.system('rm input.txt')
