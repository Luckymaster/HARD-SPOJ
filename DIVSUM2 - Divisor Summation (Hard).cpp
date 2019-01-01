#include<iostream>
#include<map>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<vector>
#include<bits/stdc++.h>
typedef long long int64;
typedef unsigned long long  uint64;
#define max_uint64 9223372036854775807LL
using namespace std;
#define MAX 10000
short p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};
vector<bool>prime(MAX,true);
void gen_primes() 
    { 
      int i,j; 
       for(i=2;i<=(int)sqrt(MAX);i++) 
         if (prime[i]) 
           for(j=i;j*i<MAX;j++) prime[i*j] = false; 
    }
map<uint64,unsigned> m1;
void save_factors(uint64);
long long mulmod(long long a,long long b,long long c);
inline uint64 scan()
    {
        uint64 z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void fastWrite(uint64 a)
{
    char snum[20];
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

inline void updateit(uint64 &phi1,uint64 n, unsigned p)
{
if(p==1) phi1 *= (n+1);
else phi1 *= ((pow(n,p+1)-1)/(n-1));
}
inline uint64 modulo(uint64 a,uint64 b,uint64 c){
    uint64 x=1,y=a; 
    while(b > 0){
        if(b&1){
            x=mulmod(x,y,c);
        }
        y = mulmod(y,y,c); 
        b>>=1;
    }
    return x%c;
}
 
inline long long mulmod(long long a,long long b,long long mod ){   
    long long res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
int pp[3]={2,3,5};
bool miller(uint64 p,int it=3){
    if(p<2){
        return false;
    }
    if((p < MAX)&&(prime[p])) return true;
    if(p!=2 && p%2==0){
        return false;
    }
    long long s=p-1;
    while(!(s&1)){
        s>>=1;
    }
    for(int i=0;i<it;i++){
        uint64 a=pp[i],tt=s;
        uint64 md=modulo(a,tt,p);
        while(tt!=p-1 && md!=1 && md!=p-1){
            md=mulmod(md,md,p);
            tt <<= 1;
        }
        if(md!=p-1 && !(tt&1)){
            return false;
        }
    }
    return true;
}
inline int64 gcd(int64 u,int64 v)
{
    int64 shift, diff;
    
    if (u == 0 || v == 0)
        return u | v;
    

    for (shift = 0; ((u | v) & 1) == 0; ++shift)
    {
        u >>= 1;
        v >>= 1;
    }
    
    while ((u & 1) == 0)
        u >>= 1;

    do {
        while ((v & 1) == 0)
            v >>= 1;
            


        if (u < v)
            v -= u;
        else
        {
            diff = u - v;
            u = v;
            v = diff;
        }
        v >>= 1;
    
    } while (v != 0);
    
    return u << shift;
}
uint64 brent_pollard_factor(uint64 n)
{
   const uint64 m = 50;
   uint64 a, x, y, ys, r, q, g;
   do
      a = random() % n;
   while(a==0||a==n-2);
   y = random() % n;
   r = 1;
   q = 1;
 
   do {
      x = y;
      for(int i=0; i < r; i++) {

         y = mulmod(y, y, n);
         y += a;
         if(y < a)
            y += (max_uint64 - n) + 1;
         y %= n;
      }
 
      uint64 k =0;
      do {
         for(uint64 i=0; i < m && i < r-k; i++) {
            ys = y;

            y = mulmod(y, y, n);
            y += a;
            if(y < a)
               y += (max_uint64 - n) + 1;
            y %= n;

            q = mulmod(q, (x>y)?x-y:y-x, n);
         }
         g = gcd(q, n);
         k += m;
      } while(k < r && g == 1);
 
      r <<= 1;
   } while(g == 1);
 
   if(g == n) {
      do {

         ys = mulmod(ys, ys, n);
         ys += a;
         if(ys < a)
            ys += (max_uint64 - n) + 1;
         ys %= n;
 
         g = gcd((x>ys)?x-ys:ys-x, n);
      } while(g == 1);
   }
 
   return g;
}

inline void factor(uint64 n)
{
	if(n==1)
		return;
    if((n < MAX)&&(prime[n]))
	    { m1[n]+=1;return;}
	else{
	if(miller(n))
	{
		
		m1[n]+=1;
		return;
		
	}}
	uint64 d=brent_pollard_factor(n);
	factor(d);
	factor(n/d);
}

inline int64 small_f(int64 n)
{   
	int ind=0;
	int64 ret,sq,pp;
	pp=p[0];
	while(n>1 && ind <=150)
	{
		while(n%pp==0)
		{
			m1[pp]+=1;
			n/=pp;
			
		}
	ind++;
	if(ind<150)pp=p[ind];
	}
	return n;
}
int main()
{
	int t;
	uint64 n,m;
	gen_primes();
	scanf("%d",&t);
	while(t--)
	{
		n=scan();
		map<uint64,unsigned>::iterator it1;
		uint64 phi1=1;
		m=small_f(n);
		factor(m);
		bool flag=false;
		for(it1=m1.begin();it1!=m1.end();it1++)
		{
			
 
			updateit(phi1,(it1->first),(it1->second));
			
             		
		}
		fastWrite(phi1-n);
		m1.clear();
		
	}
	return 0;
}
