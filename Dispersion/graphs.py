import os as os
import numpy as np
import matplotlib.pyplot as plt
import argparse
import sys

if __name__ == '__main__':
    k = []
    grid_step = 0.05
    rootss = []
    for step in range(20, 200):
        number = grid_step * step
        with open(f'Data/0_01/alpha_0.010000k_{"%.6f" % (-grid_step * step)}_.txt') as an:
            data = np.array([np.array(i.split(), dtype=float) for i in an.readlines()])
        data = np.round(data, 4)
        roots = [i.split() for i in np.unique([str(i[0]) + " " + str(i[1]) for i in data])]
        copy_roots = roots.copy()

        for i in range(len(copy_roots)):
            if copy_roots[i][1] == '-0.0' or copy_roots[i][0] == '-0.0':
                roots.remove(copy_roots[i])
            if copy_roots[i][0] == 'nan' or copy_roots[i][0] == '-inf' or copy_roots[i][0] == 'inf' \
                    or copy_roots[i][1] == 'nan' or copy_roots[i][1] == '-inf' or copy_roots[i][1] == 'inf':
                roots.remove(copy_roots[i])

        k.append("%.3f" % (grid_step * step))
        rootss.append(roots)

    plot_roots = [[], [], [], [], [], [], [], []]
    k_r = [[], [], [], []]

    for i in range(len(rootss)):
        for r in range(4):
            try:
                plot_roots[2 * r].append(float(rootss[i][r][0]))
                plot_roots[2 * r + 1].append(float(rootss[i][r][1]))
                k_r[r].append(k[i])
            except:
                pass
    label = ['Real', 'Image']
    colors = ['red', 'green', 'blue', 'magenta']
    for r in range(4):
        plt.scatter([float(i) for i in k_r[r]], [float(i) for i in plot_roots[2*r]], label='Real', s=7, color=colors[r], marker='*')
        plt.scatter([float(i) for i in k_r[r]], [float(i) for i in plot_roots[2*r + 1]], label='Image', s=7, color=colors[r], marker='o')
    plt.legend()
    plt.show()
