from sys import stdin

def solve(a, b, c):
  for i in range(10, 101):
    if i % 3 == a and i % 5 == b and i % 7 == c:
      print i
      return
  print 'No answer'

a, b, c = map(int, stdin.readline().strip().split())
solve(a, b, c)
