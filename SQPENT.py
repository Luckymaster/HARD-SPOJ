#https://oeis.org/A046172
f=[0]*2502
f[1]=1
f[2]=81
for i in xrange(3,2501):
	f[i] = 98*f[i-1] - f[i-2] - 16
t=input()
mod = 2*3367900313
for cs in xrange(t):
	n=input()
	print ((3*f[n] * f[n] - f[n] ) % mod)//2 
