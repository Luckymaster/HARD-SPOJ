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
const int MAX1 = 100005;
const int MAX = 100005;
bool g9 = false;
#define LL unsigned long long
unsigned phi_val[] = {400000000,160000000,64000000,25600000,10240000,4096000,1638400,655360,262144,131072,65536,32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1};
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

inline unsigned fi(unsigned n) 
{
	unsigned x = lower_bound(phi_val,phi_val+27,n)-phi_val;
	return phi_val[x-1];
}

inline LL modpow(unsigned a, unsigned b, unsigned c)
{
	LL x=1,y=a;
	while(b)
	{
		if(b&1)
		{
			x = x*y;
			if(x>=c){
				x%=c;
				g9=true;
			}
		}
		y = y*y;
		if(y>=c)
		{
			y%=c;
			g9=true;
		}
		b>>=1;
	}
	return x;
}
unsigned reducetower(unsigned b, unsigned  mod,unsigned i)
{
	unsigned n, rz,log2p;
	if(b%mod==0)return 0;
	if(i==2) return modpow(b,b,mod);
	if(b==2 && i==3 && mod>16) return 16;
	if(b==2 && i==4 && mod>65536) return 65536;
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
	sort(phi_val,phi_val+27);
	unsigned tc;
	unsigned n,x,mod;
	tc=scan();
	while(tc--)
	{
	
		x=scan();n=scan();mod=1000000000;
		g9=false;
		if(x==0&&n==0){
			printf("%d\n",1);
			continue;
		}
		if(x%mod==0){
			if(n==0 && mod)printf("%d\n",1);
			else if(x==0 && !(n&1))printf("1\n");
			else if(x==0 && (n&1))printf("0\n");
			else printf("...%09d\n",0);
			continue;
		}
		if(n==1){
			if(x>=mod)printf("...%09d\n",x%mod);
			else printf("%d\n",x);continue;
		}
		if(n==0){
			printf("1\n");
			continue;
		}
		if(n==2 && x < 11)
		{
			g9=false;
			LL v = powl(x,x);
			if(v >= mod)printf("...%09d\n",v%mod);
			else printf("%d\n",v);
			continue;
		}
		LL r = reducetower(x,mod,n);
		if(g9)printf("...%09d\n",r);
		else fastWrite(r);
		
	}
	
}
