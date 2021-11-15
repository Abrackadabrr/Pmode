import os as os
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def period_parse(ang):
    indexes = []
    for n in range(ang.size - 1):
        if (not ang[n]) and (ang[n + 1]):
            indexes.append(n + 1)
    return indexes


if __name__ == '__main__':
    is_diss = True
    p = pd.read_csv("cmake-build-debug/periodic.csv", sep=';')
    time = np.array(p['T'])
    angle = np.array(p['Phi'])
    bool_angle = angle > 0

    energy = np.array(p['En'])
    rel_en_err = np.array(energy) / energy[0] - 1
    velocity = np.array(p['Der'])
    omega = p['Om'][0]
    try:
        decr = p['Decr'][0]
    except:
        is_diss = False
    else:
        if not decr:
            is_diss = False

    time_step = time[1] - time[0]

    fig, ax = plt.subplots(ncols=2, nrows=2)
    if is_diss:
        fig.suptitle(f"Шаг {time_step}, квадрат омеги {omega}, декремент {decr}")
    else:
        fig.suptitle(f"Шаг {time_step}, квадрат омеги {omega}")

    ax[0][0].plot(time, angle)
    ax[0][0].set_title(f"Угол от времени")

    ax[1][0].plot(time, velocity)
    ax[1][0].set_title(f"Производная угла от времени")

    ax[0][1].plot(angle, velocity)
    ax[0][1].set_title(f"Фазовая плоскость")
    if is_diss:
        ax[1][1].plot(time, np.log(energy),
                      label=fr'k = {np.round(np.polyfit(time, np.log(energy), 1)[0], 4)}$\approx -2\gamma$')
        ax[1][1].set_title(f"Зависимость логарифма полной энергии системы от времени")
        ax[1][1].legend()
    else:
        ax[1][1].plot(time, rel_en_err)
        ax[1][1].plot(time, (np.array([0] * len(energy))), color='red')
        ax[1][1].set_title(f"Относительная ошибка интеграла движения")

    for f in ax:
        for i in f:
            i.grid()
    plt.show()
'''
    fig, ax = plt.subplots()
    if is_diss:
        fig, (ax, ox) = plt.subplots(ncols=2)
        ox.plot(time, energy, label=fr'k = {np.round(np.polyfit(time, np.log(energy), 1)[0], 4)} $\approx -2\gamma$')
        ox.plot(time, energy[0] * np.exp(np.polyfit(time, np.log(energy), 1)[0] * time),
                label=r'Аппроксимация $E_{0}e^{-2\gamma t}$')
        ox.set_title(f"Зависимость полной энергии системы от времени,\n  квадрат омеги {omega}, декремент {decr}")
        ox.legend()
        ox.grid()

    ind = period_parse(bool_angle)
    periods = np.array([time[ind[i + 1]] - time[ind[i]] for i in range(len(ind) - 1)])
    ax.plot(np.arange(1, len(periods) + 1), periods, color='green')
    ax.scatter(np.arange(1, len(periods) + 1), periods, color='red')
    ax.set_title(f"Зависимость периода колебаний,\n от номера колебания")
    ax.grid()
    plt.show()
'''