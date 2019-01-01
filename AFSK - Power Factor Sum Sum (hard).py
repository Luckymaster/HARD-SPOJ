import sys,math
first=0
second=0
def power(n,k,mod):
	if k==0:
		return n%mod
	if k==1:
		x = n*(n+1)
		return x//2
	if k==2:
		x = (2*n**3 + 3*n**2 + n )
		return x//6
	if k==3:
		y = n**3
		x = (n*y + 2*y + n**2)
		return x//4
	if k==4:
		y = n**4
		x = (6*y*n + 15*y + 10*y//n -n )
		return x//30
	if k==5:
		x = (2*n**6 +6*n**5 + 5*n**4 - n**2)
		return x//12
	if k==6:
		y = n**6
		x = ( 6*n*y + 21*y + 21*y//n -7*n**3 + n)
		return x//42
	if k==7:
		y = n**7
		x = ( 3*n*y + 12*y + 14*y//n - 7*n**4 + 2*n**2)
		return x//24
	if k==8:
		y = n**8
		x = (10*n*y +45*y + 60*y//n -42*n**5+20*n**3-3*n)
		return x//90
	if k==9:
		y = n**9
		x = (2*n*y +10*y +15*y//n-14*n**6+10*n**4-3*n**2)
		return x//20
	if k==10:
		y = n**10
		x = (6*n*y + 33*y + 55*y//n -66*n**7 + 66*n**5-33*n**3+5*n)
		return x//66
def summ(a,b,k,mod):
	global second;global first
	if second > 0:
		first = second
		second = power(b,k,mod)
	else:
		first = power(a,k,mod)
		second = power(b,k,mod)
	x = first-second
	if x<0:x+=mod
	return x;
def main():
	T=int(input())
	for cs in range(T):
		global first
		global second
		first = 0 ;second = 0;
		kk, m ,mod = map(int,sys.stdin.readline().split())
		k=0;ansk = 0;anskk = 0;tempk = 0;tempkk = 0
		sqrtkk = int(math.sqrt(kk))
		sqrtk = 0
		for j in range(1,sqrtkk+1):
			tempkk = pow(j,m)
			tempk = tempkk
			tempkk = tempkk*(kk//j)
			anskk = anskk + tempkk
			if((kk//j)>=sqrtkk+1  and int(math.sqrt(kk))>=j):
				anskk+=(j*summ(kk//j,kk//(j+1),m,mod))
			j+=1
		print (anskk%mod)
main()

