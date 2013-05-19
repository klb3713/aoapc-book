from sys import stdin
from math import *
r, h = map(float, stdin.readline().strip().split())
print "Area = %.3lf" % (pi*r*r*2 + 2*pi*r*h)
