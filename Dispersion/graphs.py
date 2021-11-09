import numpy as np
import matplotlib.pyplot as plt
from itertools import accumulate as acc


# арцемович физика плазмы для физиков


def find_maximum_of_image_parts(rootz):
    return max([[max(parse_image_part(roots)), index] for index, roots in enumerate(rootz)], key=lambda i: i[0])


def parse_real_part(_roots):
    return list(acc(_roots))[-1][0::2]


def parse_image_part(_roots):
    return list(acc(_roots))[-1][1::2]


def find_roots(_data):
    _roots = [i.split() for i in np.unique([str(i[0]) + " " + str(i[1]) for i in _data])]
    copy_roots = _roots.copy()

    for i in range(len(copy_roots)):
        if copy_roots[i][1] == '-0.0' or copy_roots[i][0] == '-0.0':
            _roots.remove(copy_roots[i])
    _roots = [[float(i[0]), float(i[1])] for i in _roots]
    return _roots


def read_data(filename):
    with open(filename) as file:
        lines = file.readlines()
    dat = []
    headers = []
    i = -1
    for line in lines:
        line = np.round(np.array(line.split(), dtype=float), 4)
        if len(line) == 2:
            i += 1
            headers.append(line)
            dat.append([])
        else:
            dat[i].append(line)
    return dat, headers


def check_assimptota(rootz, headz):
    x_ = []
    y = []
    first_index = find_multiple_root(rootz)
    print(first_index)
    require_real_parts = [sorted(parse_real_part(roots), reverse=True)[0:2:1] for index, roots in enumerate(rootz) if
                          index >= first_index]
    for i, root in enumerate(require_real_parts):
        if float(root[0]) > 1.01 and float(root[1]) > 1.01:
            index = i + first_index
            x_.append(index)
            y.append(float(root[index % 2]))
    x_ = [headz[i][1] for i in x_]
    return np.polyfit(x_, y, 1)


def find_multiple_root(_roots):
    first_index = [n for n, root in enumerate(_roots) if
                   np.abs(max(np.array(parse_image_part(root), dtype=float))) > 0.0001]
    return first_index[-1]


if __name__ == '__main__':

    for alpha in (["%.6f" % 0.001, "%.6f" % 0.05, "%.6f" % 0.3, "%.6f" % 0.7]):
        rootss = []
        data, heads = read_data(f"Data3/{alpha}.txt")
        print(len(data), len(heads), sep='; ')
        for step in range(len(data)):
            rootss.append(find_roots(data[step]))

        fig, (ax, ox) = plt.subplots(ncols=2)
        print(len(rootss), len(heads), sep='; ')
        for ind, r in enumerate(rootss):
            x = [float(heads[ind][1])] * (len(r))
            ax.scatter(x, [float(i[0]) for i in r], color='green', s=4)
            ax.scatter(x, [float(i[1]) for i in r], color='red', s=4)
            ox.scatter(x, [float(i[1]) for i in r], color='red', s=4)
        max_im_part = find_maximum_of_image_parts(rootss)
        ox.scatter(0, 0, color='red', s=4, label=f'Maximum = {max_im_part[0]} \n with k = {heads[max_im_part[1]][1]}')
        ax.grid()
        ox.grid()
        x = np.arange(0, heads[-1][1], 0.01)
        asymp_params = check_assimptota(rootss, heads)
        ax.plot(x, np.polyval(asymp_params, x), color='blue',
                label=f'asymptote with k = {np.round(asymp_params[0], 4)}\nand b = {np.round(asymp_params[1], 4)}')
        fig.suptitle(f'Alpha = {heads[1][0]}')
        ax.set_title('Roots')
        ox.set_title('Image prat')
        ox.set_xlabel(r'$\hat{k}$')
        ax.set_xlabel(r'$\hat{k}$')
        ax.legend()
        ox.legend()
        fig.set_figheight(10)
        fig.set_figwidth(14)
        plt.savefig(f'Pictures/ForGif/{alpha}.png')
        # plt.show()
