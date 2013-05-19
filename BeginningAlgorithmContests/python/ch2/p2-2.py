from sys import stdin

def cycle(n):
  if n == 1: return 0
  elif n % 2 == 1: return cycle(n*3+1) + 1
  else: return cycle(n/2) + 1

n = int(stdin.readline().strip())
print cycle(n)
