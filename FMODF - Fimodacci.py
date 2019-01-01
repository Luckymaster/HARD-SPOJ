import sys
fibk = []
def fibb():
	fibk.append(0);fibk.append(1);fibk.append(1);
	for i in range(3,4001,1):
		fibk.append(fibk[i-1]+fibk[i-2])
fibb()
t=int(sys.stdin.readline())
while(t > 0):
	prds=0
	x,n=map(int,sys.stdin.readline().split())
	if(n&1):
		prds = n<<2
	else:
		prds = n<<1
	x%=prds
	if x < 4001:
		if(x%n==0):
			print("0");
		else:
			print'{0}'.format(fibk[x]%fibk[n])
	t=t-1
