from sys import stdin
n, m = map(int, stdin.readline().strip().split())
a = (4*n-m)/2
b = n-a
if m % 2 == 1 or a < 0 or b < 0: print "No answer"
else: print a, b

