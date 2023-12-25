import os
import numpy as np
import matplotlib.pyplot as plt

UFS=np.array([2, 4, 8, 16, 32])
L1S=np.array([2, 4, 8, 16, 32, 64])
UF_FILE="unrolling-factors.txt"
L1_FILE="l1-cache.txt"

def read_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    lines = [line.strip() for line in lines]
    lines = [line.split() for line in lines]
    cycles = np.array([float(line[1]) for line in lines])
    return cycles

if __name__ == "__main__":
    cycles_uf = read_file(UF_FILE)
    cycles_l1 = read_file(L1_FILE)
    
    plt.figure()
    plt.plot(UFS, cycles_uf)
    plt.xticks(UFS)
    plt.xlabel("Unrolling Factor")
    plt.ylabel("Cycles")
    plt.grid()
    plt.title("Unrolling Factor vs Cycles")
    plt.savefig("./plots/unrolling-factor.png")
    
    plt.figure()
    plt.plot(L1S, cycles_l1)
    plt.xticks(L1S)
    plt.xlabel("L1 Cache Size")
    plt.ylabel("Cycles")
    plt.grid()
    plt.title("L1 Cache Size vs Cycles")
    plt.savefig("./plots/l1-cache.png")
    plt.show()

