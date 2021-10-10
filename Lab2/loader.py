import os as os
import numpy as np
import matplotlib.pyplot as plt
import argparse
import sys
    
if __name__ == '__main__':
    
    os.system("g++ simple_integral.cpp -o simp_int")
    os.system("./simp_int")
    points = []
    with open("input.txt") as inputt:
        points = np.array([i for i in inputt.readlines()])
    X = np.array([float(i.split()[0]) for i in points])
    Y1 = np.array([float(i.split()[1]) for i in points])
    #Y2 = np.array([float(i.split()[2]) for i in points])
    plt.plot(X, Y1)
    #plt.plot(X, Y2)
    plt.grid()
    plt.show()

    os.system("rm simp_int")
    os.system("rm input.txt")    

