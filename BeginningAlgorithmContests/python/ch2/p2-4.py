from sys import stdin
a = map(int, stdin.readline().strip().split())
print "%d %d %.3lf" % (min(a), max(a), float(sum(a)) / len(a))
