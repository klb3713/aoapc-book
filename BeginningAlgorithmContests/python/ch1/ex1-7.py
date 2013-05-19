from sys import stdin
n, = map(int, stdin.readline().strip().split())
money = n * 95
if money >= 300: money *= 0.85
print "%.2lf" % money
