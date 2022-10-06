from random import randint
import sys
import os

#Usage: gen_rand_inputs.py n p r -> generate random ints 

n = int(sys.argv[1]) # number of inputs
p = int(sys.argv[2]) # number of players
m = int(sys.argv[3]) # maximum Value of random inputs

# generate random player 1 data

# generate random player 0 data
for i in range(p):
    f = open("./Player-Data/Input-P" +str(i)+ "-0", "w")
    for i in range(n):
        f.write(str(randint(0, m)) + " ")
    f.close()

