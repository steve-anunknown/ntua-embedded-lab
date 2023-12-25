import pandas as pd
import numpy as np
from paretoset import paretoset
from matplotlib import pyplot as plt

# create a panda dataframe
# with two columns
# one totalMemoryKB that is the sum of the memory of all caches
# two latencyCC that are the total cycles for the execution of the program

def read_gen_data(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    # the data are in csv format
    # we need only the latencyCC and totalMemoryKB
    lines = [line.strip() for line in lines]
    lines = [line.split(",") for line in lines]
    cycles = np.array([float(line[4]) for line in lines[1:]])
    memory = np.array([float(line[5]) for line in lines[1:]])
    return cycles, memory

dictionary = {
        "totalMemoryKB": [],
        "latencyCC": []
        }
# read the file
with open("combinations.csv") as f:
    # for each line
    architecture=[]
    for line in f:
        if line.startswith('cycles'):
            continue
        numbers = [ int(el) for el in line.split(",") ]
        latency = numbers[0] 
        memory = numbers[1] + numbers[2] + numbers[3]
        architecture.append(line.split(",")[1:])
        # append the line to the dataframe
        dictionary["totalMemoryKB"].append(memory)
        dictionary["latencyCC"].append(latency)

# find the pareto frontier
design_space = pd.DataFrame(dictionary)
mask = paretoset(design_space, sense=["min", "min"])
paretoset = design_space[mask]

gen_cycles, gen_memory = read_gen_data("genOptimizer_PO.csv")
gen_dic = {
        "totalMemoryKB": gen_memory,
        "latencyCC": gen_cycles
        }
gen_df = pd.DataFrame(gen_dic)

# plot the pareto frontier
plt.figure(figsize=(12, 8), dpi=100)  # Adjust as needed
plt.title("Cycles and Memory Pareto Frontier")
plt.scatter(design_space["totalMemoryKB"],
            design_space["latencyCC"],
            zorder=20,
            label="Design Space",
            s=25,
            alpha=0.4)
plt.scatter(paretoset["totalMemoryKB"],
            paretoset["latencyCC"],
            zorder=10,
            label="Pareto Frontier",
            s=75,
            alpha=1)
plt.scatter(gen_df["totalMemoryKB"],
            gen_df["latencyCC"],
            zorder=30,
            label="Genetic Algorithm",
            s=75,
            alpha=1)
plt.xlabel("Total Memory (KB)")
plt.ylabel("Cycles")
# connect pareto points with a line
pareto_points = paretoset[["totalMemoryKB", "latencyCC"]].values
pareto_points = pareto_points[np.argsort(pareto_points[:, 0])]
plt.plot(pareto_points[:, 0], pareto_points[:, 1], c="C1")
# connect genetic algorithm points with a line
gen_points = gen_df[["totalMemoryKB", "latencyCC"]].values
gen_points = gen_points[np.argsort(gen_points[:, 0])]
plt.plot(gen_points[:, 0], gen_points[:, 1], c="C2")

plt.legend()
plt.savefig("./plots/pareto.png")
plt.show()


archs = np.array(architecture)
archs = archs[mask] # list of lists of 4 elements
archs = [",".join(el) for el in archs]

# write pareto points and architectures to csv
with open("pareto.csv", "w") as f:
    f.write('latencyCC,totalMemoryKB,l1i,l1d,l2,uf\n')
    for i in range(len(paretoset)):
        f.write(str(paretoset.iloc[i]['latencyCC']) + "," + str(paretoset.iloc[i]['totalMemoryKB']) + "," + str(archs[i]))

