from sys import stdin
a, b, c = map(int, stdin.readline().strip().split())
print "%.3lf" % ((a+b+c)/3.0)
