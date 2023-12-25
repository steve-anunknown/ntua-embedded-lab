

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

df = pd.DataFrame({'Max Time': [1.6339916, 0.8420916, 0.881944583, 0.778483, 0.82312083],
                   'Min Time': [1.6339916, 0.8420833, 0.881944583, 0.778475, 0.8231125],
                   'Mean Time': [1.6339916, 0.84208416, 0.881944583, 0.7784758, 0.8231113]})

# plot only mean time as np array
mean_time = np.array([1.6339916, 0.84208416, 0.881944583, 0.7784758, 0.8231113])
# make figure bigger
plt.figure(figsize=(10, 7))
plt.plot(mean_time)
plt.xticks(range(len(mean_time)), ['Loop Fusion','cached comp','init Loop Trans','Block Cache','Line Cache'], rotation=-15)
plt.title('Execution Time per Optimization')
plt.ylabel('Time (ms)')
plt.xlabel('Optimization')
plt.savefig("./plots/measurements.png")
plt.grid()
plt.savefig("./plots/measurements.png")

current_line = np.array([
    [.00134679583, .00134679583, .00134679583],
    [.0011057, .0011056916, .0011056925],
    [.00098008, .00098008, .00098008],
    [.000910079,  .0009100708, .0009100716],
    [.00105109, .00105109, .00105109],
    [.000945575, .000945575, .000945575],
    [.0008856417, .0008856417, .0008856417],
    [.0008498375, .00084982916, .00084983],
    [.00087090416, .00087091250, .000870905],
    [.00084077, .00084077, .00084077],
    [.00082312083, .0008231125, .0008231113],
    [.00082049583, .00082049583, .00082049583],
    [.0008243, .0008243, .0008243],
    [.0008116, .0008115917, .0008115925],
    [.0008180583, .0008180583, .0008180583],
    [.000807066,  .0008070583, .0008070592]
])
#

block_buffer = np.array([
    [.0013277875, .0013277875, .0013277875], # (1, 1)
    [.0010650875, .0010650875, .0010650875], 
    [.0009038583, .000903850, .0009038508],
    [.00085426, .00085426, .00085426],
    [.00103017083, .0010301625, .00103016333],
    [.000896475, .000896483, .00089647583], # (2, 2)
    [.00081647083, .00081647083, .00081647083],
    [.0007941583, .0007941583, .0007941583],
    [.000845683, .000845675, .00084567583],
    [.00079512083, .0007951125, .0007951133],
    [.000778475, .000778463, .0007784758], 
    [.0007931083, .0007931083, .0007931083],
    [.00079135833, .00079135833, .00079135833],
    [.00078140416, .00078139583, .000781396],
    [.0007953083, .0007953083, .0007953083],
    [.00077700416, .00077699583, .000776997]
])

# keep the 2nd element of each row
current_line_dse = current_line[:, 1] * 1000
block_dse = block_buffer[:, 1] * 1000

# plot block buffer dse for Bx = By = B (B = 1, 2, 5, 10)
plt.figure()
plt.plot(block_dse[0::5], label="Block Buffer")
plt.plot(current_line_dse[0::5], label="Current Line")
plt.xticks(range(len(block_dse[0::5])), [1, 2, 5, 10])
plt.xlabel("B")
plt.ylabel("Time (ms)")
plt.title("Design Space Exploration of B")
plt.grid()
plt.legend()
plt.savefig("./plots/dse-b.png")


plt.figure()
plt.plot(current_line_dse, label="Current Line")
plt.plot(block_dse, label="Block Buffer")
# xticks are cartesian product of [1, 2, 5, 10] and [1, 2, 5, 10]
xticks = [1, 2, 5, 10]
xticks = [(x, y) for x in xticks for y in xticks]
plt.xticks(range(len(xticks)), xticks, rotation=30)
plt.xlabel("(Bx, By) Size")
plt.ylabel("Time (ms)")
plt.title("Design Space Exploration of (Bx, By) Size")
plt.grid()
plt.legend()
plt.savefig("./plots/dse.png") 



