#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
using namespace std;
const int MAX = 65536;
vector<bool>prime(MAX,true);
vector<unsigned short>p;
#define LL unsigned long long
inline unsigned scan()
    {
        unsigned z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }

inline void fastWrite(unsigned a)
{
    char snum[25];
    int i=0;
    do
    {
        snum[i++]=a%10+'0';
        a=a/10;
    }
    while (a);
    i=i-1;
    while (i>=0)
        putchar_unlocked(snum[i--]);
    putchar_unlocked('\n');
}
inline void gen_primes() 
{
	unsigned short i,j,c=0; 
	prime[0]=prime[1]=false;
	for(i=2;i<=(int)sqrt(MAX);++i) 
	{
		if (prime[i])
		{
			for(j=i;j*i<MAX;++j)
			{
				prime[i*j] = false; 
			}
		}
	}
	p.push_back(2);
	for(int i=3;i<MAX;i+=2)
	{
		if(prime[i])
		{
			p.push_back(i);
			
		}
	}
       
}

inline unsigned fi(unsigned n) 
{
	{
		unsigned i, result = n; 
		for(i=0;p[i]*p[i] <= n;++i) 
		{ 
			if (n %p[i] == 0) result -= result /p[i]; 
			while (n %p[i] == 0) n /= p[i]; 
		} 
		if (n > 1) result -= result / n; 
		return result; 
    }
}

inline unsigned modpow(unsigned a, unsigned b, unsigned c)
{
	unsigned x=1,y=a;
	while(b)
	{
		if(b&1)
		{
			x =(LL)x*y%c;

		}
		y = (LL)y*y%c;
		b>>=1;
	}
	return x;
}
unsigned reducetower(unsigned b, unsigned mod,unsigned i)
{
	unsigned n, rz,log2p;
	if(b%mod==0) return 0;
	if(i==2) return modpow(b,b,mod);
	if(b==2 && i==3 && mod>16) return 16;
	if(b==2 && i==4 && mod>65536) return 65536;
	if(b==3 && i==3 && mod>7625597484987LL) return 7625597484987LL;
	log2p = 0;
	n = fi(mod);
	if(n+1<mod)
	{
		log2p=floor(log(mod)/log(2));
	}
	rz = reducetower(b,n,i-1);
	while((log2p>0) && (rz<log2p))
	{
		rz=rz+n;
	}
	rz = modpow(b,rz,mod);
	return rz;
}
int main()
{
	gen_primes();
	unsigned tc;
	unsigned n,x,mod;
	tc=scan();
	while(tc--)
	{
		x=scan();n=scan();mod=scan();
		if(x==0&&n==0){
			printf("%d\n",1%mod);
			continue;
		}
		if(x%mod==0){
			if(n==0 && mod)printf("%d\n",1%mod);
			else if(x==0 && n%2==0)printf("%d\n",1%mod);
			else puts("0");
			continue;
		}
		if(n==1){
			printf("%u\n",x%mod);
			continue;
		}
		if(n==0){
			printf("%u\n",1%mod);
			continue;
		}
		if(n==2 && x < 11){
		LL v = pow(x,x);
			printf("%u\n",v%mod);
			continue;
		}
		LL r = reducetower(x,mod,n);
		fastWrite(r);
	}
	
}
















