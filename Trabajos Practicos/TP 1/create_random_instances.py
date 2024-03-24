import numpy as np

np.random.seed(2022)

for power in range(16, 27):
    n = 2 ** power
    f = open("inputs/input_" + str(n), "w")
    input = np.random.randint(2,2*n+1,n)
    for num in input:
        s = str(np.random.randint(1,num)) + " "
        t = str(num) + " "
        f.write(s)
        f.write(t)

    f.close()
