from sys import stdin
from math import *
x1, y1, x2, y2 = map(float, stdin.readline().strip().split())
print "%.3lf" % hypot((x1-x2), (y1-y2))
