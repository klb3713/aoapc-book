from sys import stdin
from math import *
n, = map(int, stdin.readline().strip().split())
rad = radians(n)
print "%.3lf %.3lf" % (sin(rad), cos(rad))
