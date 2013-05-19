from sys import stdin
n = int(stdin.readline().strip())
count = n*2-1
for i in range(n):
  print ' '*i + '#'*count
  count -= 2
