import sys
def fib(n, m):
    if n == 0:
        return (0, 1)
    else:
        a, b = fib(n // 2, m)
        if b>= m:
            b %= m
        c = a * (2*b - a)
        if c >= m or c < 0:
            c %= m
        d = (b * b + a * a)
        if d >= m:
            d %= m
        if n & 1:
            return (d, c + d)
        else:
            return (c, d)
def solve():
	t=int(sys.stdin.readline())
	for cs in xrange(t):
		n,x = map(int,sys.stdin.readline().split())
		mod = 1000000007
		b = (x**2 + x -1)
		mod = mod * b
		x1 = pow(x,n + 1, mod)
		x2 = x1 * x % mod
		fb = fib(n,mod)
		res = fb[0] * x2 + fb[1] * x1 - x
		res = (res + mod)%mod
		print res/b
solve()
