s = i = 0
while True:
  term = 1.0 / (i*2+1)
  s += term * ((-1)**i)
  if term < 1e-6: break
  i += 1
print "%.6lf" % s
