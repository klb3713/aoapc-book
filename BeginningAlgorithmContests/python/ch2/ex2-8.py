from sys import stdin
n, m = map(int, stdin.readline().strip().split())
print "%.5lf" % sum([1.0/i/i for i in range(n,m+1)])
