import matplotlib.pyplot as plt
import numpy as np


file_name = input("input file name:")
file_1 = open(file_name, "r")
line_1 = file_1.readline()
ignore = "Total"

def get_score (line_1):
    lin = line_1.strip('\n')
    lin = lin.split('\t')
    num = lin[-1]
    if ignore not in num:
        return int(num)


arr = []
while line_1:
    score = get_score(line_1)
    arr.append(score)
    line_1 = file_1.readline()
print(arr)

data = np.array(arr)
plt.hist(data, 220)
plt.xlabel("Numbers of reads of each coding sequence")
plt.ylabel("log(10)")
plt.yscale('log')
plt.title('Histogram of Numbers of Coding Sequence Reads Raw Data')
plt.show()
file_1.close()
