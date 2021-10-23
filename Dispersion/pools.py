import os as os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

if __name__ == '__main__':

    with open('Data/0_001/alpha_0.001000k_1.900000_.txt') as an:
        data = np.array([np.array(i.split(), dtype=float) for i in an.readlines()])
    data = np.round(data, 4)

    roots = [i.split() for i in np.unique([str(i[0]) + " " + str(i[1]) for i in data])]
    copy_roots = roots.copy()

    for i in range(len(copy_roots)):
        if copy_roots[i][1] == '-0.0' or copy_roots[i][0] == '-0.0':
            roots.remove(copy_roots[i])
        if copy_roots[i][0] == 'nan' or copy_roots[i][0] == '-inf' or copy_roots[i][0] == 'inf'\
                or copy_roots[i][1] == 'nan' or copy_roots[i][1] == '-inf' or copy_roots[i][1] == 'inf':
            roots.remove(copy_roots[i])

    print(roots)

    colors = ['red', 'green', 'blue', 'magenta']

    plt.scatter([float(i[0]) for i in roots], [float(i[1]) for i in roots], color=colors[:len(roots)], s=12)
    for ind, root in enumerate(roots):
        p = [[point[3], point[4]] for point in data if float(roots[ind][0]) == point[0] and float(roots[ind][1]) == point[1]]
        plt.scatter([i[0] for i in p], [i[1] for i in p], color=colors[ind], s=2)
    plt.grid()
    plt.gca().set_aspect('equal')
    plt.show()
