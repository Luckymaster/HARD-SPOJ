import random
import sys
import math
pre=[]
mod=1000000007
def rwh_primes(n):
    sieve = [True] * n
    m=int(math.sqrt(n))
    for i in range(3,int(m)+1,2):
        if sieve[i]:
            sieve[i*i::(i<<1)]=[False]*((n-i*i-1)//(i<<1)+1)
    return [2] + [i for i in range(3,n,2) if sieve[i]]
def millerRabin(N,iteration=3):
        if N<2:
                return False
        if N!=2 and N%2==0:
                return False
         
        d=N-1
        while d%2==0:
                d = d//2
         
        for i in range(iteration):
                a = random.randint(1, N-1)
                temp = d
                x = pow(a,temp,N)
                while (temp!=N-1 and x!=1 and x!=N-1):
                        x = (x*x)%N
                        temp<<=1
                 
                if (x!=N-1 and temp%2==0):
                        return False
         
        return True
def factor(n,prime):
	maxL = len(prime)
	power=0;odd=0;even=1;ind=0;k=0
	p=prime[0]
	while(n>1 and ind < maxL):
		power=0
		while(n%p==0):
			power+=1
			n//=p
		even*=(power+1)
		ind+=1
		if(ind < maxL):
			p=prime[ind]
	if(n > 1):
		sq = int(n**0.5)
		if(sq*sq==n):
			even*=3
		elif(millerRabin(n)):
			even*=2
		else:
			even*=3
	return even
def main():
	p=rwh_primes(200007)
	t=int(sys.stdin.readline())
	for cs in sys.stdin:
		n=int(cs)
		dn = factor(n,p)
		sq = int(n**.5)
		
		if sq*sq == n:
			print sq*pow(n,dn//2,mod)%mod
		else:
			print pow(n,dn//2,mod)
main()
