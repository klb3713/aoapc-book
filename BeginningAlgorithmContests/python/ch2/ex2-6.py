from sys import stdin
n = int(stdin.readline().strip())
print "%.3lf" % sum([1.0/x for x in range(1,n+1)])
