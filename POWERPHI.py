import sys
def fib_mod(n, mod):
  if n <= 2:
    return (((n + 1) >> 1) % mod, ((n + 2) >> 1) % mod)
  mask = 4
  while mask <= n:
    mask <<= 1
  mask >>= 2
  a, b = 1, 1
  while mask:
    if mask & n:
      a, b = (a * a + b * b) % mod, b * ((a + a) + b) % mod
    else:
      a, b = (a * ((b + b) - a) % mod), (a * a + b * b) % mod
    mask >>= 1
  return a, b
for _ in xrange(int(input())):
	n=int(sys.stdin.readline())
	v= fib_mod(n,1000000007)
	if(n==1):print"2"
	else:print(v[1]+v[1]-v[0])%1000000007
