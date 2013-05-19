from sys import stdin
from decimal import *
a, b, c = map(int, stdin.readline().strip().split())
getcontext().prec = c
print Decimal(a) / Decimal(b)
