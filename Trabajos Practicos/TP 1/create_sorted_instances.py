import numpy as np

for power in range(16, 27):
    n = 2 ** power
    f = open("inputs/input_" + str(n), "w")
    input = range(2,n+1)
    for num in input:
        s = str(np.random.randint(1,num)) + " "
        t = str(num) + " "
        f.write(s)
        f.write(t)

    f.close()
