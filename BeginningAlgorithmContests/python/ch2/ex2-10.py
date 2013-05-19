for abc in range(123, 329):
  big = str(abc) + str(abc*2) + str(abc*3)
  if(''.join(sorted(big)) == '123456789'): print abc, abc*2, abc*3
