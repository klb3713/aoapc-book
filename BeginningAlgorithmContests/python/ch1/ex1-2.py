from sys import stdin
f, = map(float, stdin.readline().strip().split())
print "%.3lf" % (5*(f-32)/9)
