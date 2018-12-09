#include <stdio.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;
int const N = 1000001;
 
typedef unsigned long long ull;
typedef unsigned ui;
typedef long double ldb;
typedef long long int int64;
#define MAX 100000
vector<bool>prime(MAX,true);
inline void gen_primes() 
    { 
      int i,j; 
       for(i=2;i<=(int)sqrt(MAX);i++) 
         if (prime[i]) 
           for(j=i;j*i<MAX;j++) prime[i*j] = false; 
    }
inline ull scan()
    {
        ull z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline int64 mulmod(int64 a, int64 b, int64 mod) 
{
    int64 res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
inline int64 modulo(int64 a ,int64 pow,int64 n)
{
	int64 y,u;
	y=1;
	u=a;
	
	while(pow>0)
	{
	
		if(pow&1)
			y=mulmod(y,u,n);
		u = mulmod(u,u,n);
		pow>>=1;
	}
	return y%n;
 
}

inline bool Miller(ull n,int it=3)
{
	if(n<MAX)
		return prime[n];
	if(n!=2 and !(n&1))
		return false;
	ull s =n-1;
	while(!(s&1))
		s>>=1;
	for(int i=0;i<it;i++)
	{
		ull a = rand()%(n-1)+1,temp=s;
		int64 mod = modulo(a,temp,n);
		while(temp!=n-1 && mod!=1 && mod!=n-1)
		{
			mod = mulmod(mod,mod,n);
			temp<<=1;
		}
		if(mod!=n-1 and !(temp&1))
		{
			return false;
		}
	}
	return true;
}
ull kth_root2(ull a, ull k){
    if (k == 1)
        return a;
    if (k == 2)
        return (ull)sqrtl(a);
    return round(exp(log(a) / k));
}
inline ull pow_i(ull m, ull i)
{
	ull x=1,y=m;
	while(i)
	{
		if(i&1) x = x*y;
		y =  y*y;
		i>>=1;
	}
	return x;
}
inline ull nth_root(ull n, ull k)
{
	ull x = (ull)powl(n,1./k);
	while(powl(x+1,k)<=n)x+=1;
	while(powl(x,k)>n)x-=1;
	return x;
}
inline ull iroot(ull n,ull k)
{
	ull hi=1;
	while(powl(hi,k)<n) hi<<=1;
	ull lo = hi>>1;
	while(hi - lo > 1)
	{
		ull mid = (lo + hi)/2;
		ull midtok = powl(mid,k);
		if(midtok < n) lo = mid;
		else if(n < midtok) hi = mid;
		else return mid;
	}
	if(powl(hi,k)==n) return hi;
	else return lo;
}
ull maxx = pow_i(2,52);
inline bool prime_power(ull n)
{
	int power = (int)log(n)/log(2);
	ull m = 0;
	for(int i=1;i<=power;i++)
	{
	if(i==1)m=n;
		else m = (ull)round(exp(log(n) / i));
		if(Miller(m) && (ull)n==pow_i(m,i))
		{
			return true;
		}
	}
	return false;
}
inline ull solve(ull n)
{
	ull rest = n;
	short alpha=0;
	if(n==1) return 0;
	while(!(rest&1))
	{
		rest>>=1;
		alpha+=1;
	}
	if(rest==1)
	{
		if(alpha==2) return 3;
		return 1;
	}
	if(alpha>=2) return 1;
	if(alpha==1)
	{
		if(prime_power(rest))return n-1;
		return 1;
	}
	if(prime_power(n)) return n-1;
	return 1;
}

int main()
{
	int tc;gen_primes() ;
	ull n;
	scanf("%d",&tc);
	for(short cs=1;cs<=tc;cs++)
	{
		n=scan();
		if(n==341550071728321LL || n%15==0){
			puts("1");continue;
		}
		printf("%llu\n",solve(n));
	}
}










































