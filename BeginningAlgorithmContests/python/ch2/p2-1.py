from itertools import product
from math import *

def issqrt(n):
  s = int(floor(sqrt(n)))
  return s*s == n  

aabb = [a*1100+b*11 for a,b in product(range(1,10),range(10))]
print ' '.join(map(str, filter(issqrt, aabb)))
