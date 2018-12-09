import sys,bisect,re,math,collections,cStringIO
def rwh_primes2(n):
    correction = (n%6>1)
    n = {0:n,1:n-1,2:n+4,3:n+3,4:n+2,5:n+1}[n%6]
    sieve = [True] * (n//3)
    sieve[0] = False
    for i in xrange(int(n**0.5)//3+1):
      if sieve[i]:
        k=3*i+1|1
        sieve[      ((k*k)//3)      ::2*k]=[False]*((n//6-(k*k)//6-1)//k+1)
        sieve[(k*k+4*k-2*k*(i&1))//3::2*k]=[False]*((n//6-(k*k+4*k-2*k*(i&1))//6-1)//k+1)
    return [2,3] + [3*i+1|1 for i in xrange(1,n//3-correction) if sieve[i]]
primes=rwh_primes2(100000100)
def main():
	T=int(input())
	inp=cStringIO.StringIO(sys.stdin.read())
	for cs in inp:
		n,M = map(int,cs.split())
		lli=0
		if n<1000000:lli=204
		else:lli=500
		d=[0]*1205
		nex=0
		prev = bisect.bisect_right(primes,n)
		for i in range(2,lli):
			nex=bisect.bisect_right(primes,n//i)
			d[i]=(prev-nex)
			prev=nex
		lm=nex
		divv = 1;divv1=1
		for i in xrange(lm):
			q=n;m=0
			p=primes[i]
			while(q >= p):
				q//=p
				m+=q
			divv*=(m+1)
			divv%=M
		for x in xrange(2,lli):
			divv*=(pow(x,d[x],M))
			divv%=M
		print(divv)
main()



