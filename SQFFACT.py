import random,sys
from fractions import gcd
def mr_pass(a, s, d, n):
    a_to_power = pow(a, d, n)
    if a_to_power == 1:
        return True
    for i in range(s - 1):
        if a_to_power == n - 1:
            return True
        a_to_power = (a_to_power * a_to_power) % n
    return a_to_power == n - 1


def is_prime(n):
    if n in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71, 79, 83, 89, 97, 101, 103, 107, 109, 113]:
        return True
    if n < 2047:prime = [2, 3]
    if n < 1373653:prime = [2, 3]
    if n < 9080191:prime = [31, 73]
    if n < 25326001:prime = [2, 3, 5]
    if n < 3215031751:prime = [2, 3, 5, 7]
    if n < 4759123141:prime = [2, 7, 61]
    if n < 1122004669633:prime = [2, 13, 23, 1662803]
    if n < 2152302898747:prime = [2, 3, 5, 7, 11]
    if n < 3474749660383:prime = [2, 3, 5, 7, 11, 13]
    if n < 341550071728321:prime = [2, 3, 5, 7, 11, 13, 17]
    if n < 3825123056546413051:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23]
    if n < 18446744073709551616:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    if n < 318665857834031151167461:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
    if n < 3317044064679887385961981:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
    else:  prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71]
    d = n - 1
    s = 0
    while d % 2 == 0:
        d >>= 1
        s += 1
    for repeat in range(len(prime)):
        a = prime[repeat]
        if not mr_pass(a, s, d, n):
            return False
    return True
def find_fact(m,phi):
    #Write phi = 2^r * s
    [r,s] = [phi,0]
    while(r%2==0):
        [r,s] = [(r//2),s+1]
    while(1):
        #Generate a random element 2 < a < m
        a = random.randint(3,m)
        #If we found are lucky then a factor is found directly
        d = gcd(a,m)
        if(1 < d < m):
            return d
        
        #Try
        #    d = gcd(a^{2^i * s)-1 , m)
        #for 0 <= i < s
        b = pow(a,r,m)
        for i in range(s):
            d = gcd(b-1,m)
            if(1 < d < m):
                return d
            b = (b**2) % m
fct=[]
def factor(n,phi):
	if n==1:
		return
	if(is_prime(n)):
		fct.append(n)
		return
	d=find_fact(n,phi)
	factor(n//d,phi)
	factor(d,phi)
	return fct
for i in range(int(sys.stdin.readline())):
	n,phi=map(int,sys.stdin.readline().split())
	if n == phi+1:
		sys.stdout.write('%d = %d\n'%(n,n))
	else:
		factor(n,phi)
		fct.sort()
		sys.stdout.write('%d = '%(n))
		for p in range(0,len(fct)-1):
			sys.stdout.write('%d * '%(fct[p]))
		print(fct[len(fct)-1])
		fct=[]
	
