from itertools import product
sol = [a*100+b*10+c for a,b,c in product(range(1,10), range(10), range(10)) if a**3+b**3+c**3 == a*100+b*10+c]
print '\n'.join(map(str, sol))
