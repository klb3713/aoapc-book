from sys import stdin
from math import *
n = int(stdin.readline().strip())
print sum(map(factorial, range(1,n+1))) % (10**6)

