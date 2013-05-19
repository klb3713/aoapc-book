from sys import stdin
a, b, c = map(int, stdin.readline().strip().split())
if a*a + b*b == c*c or a*a + c*c == b*b or b*b + c*c == a*a: print "yes"
elif a + b <= c or a + c <= b or b + c <= a: print "not a triangle"
else: print "no"
