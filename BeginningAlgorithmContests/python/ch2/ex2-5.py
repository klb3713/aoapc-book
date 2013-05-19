from sys import stdin
data = map(int, stdin.readline().strip().split())
n, m = data[0], data[-1]
data = data[1:-1]
print len(filter(lambda x: x < m, data))
