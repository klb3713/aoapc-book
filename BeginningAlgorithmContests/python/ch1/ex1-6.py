from sys import stdin
n, = map(int, stdin.readline().strip().split())
print ["yes", "no"][n % 2]
