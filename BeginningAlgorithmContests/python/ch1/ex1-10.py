from sys import stdin
from calendar import isleap
year, = map(int, stdin.readline().strip().split())
if isleap(year): print "yes"
else: print "no"
