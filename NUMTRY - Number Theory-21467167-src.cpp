#include<bits/stdc++.h>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<map>
#include<algorithm>
#define Mod 1000000007
using namespace std;
typedef long long  int64;
typedef unsigned long long uint64;
#define max_uint64 9223372036854775807LL
using namespace std;
unordered_map<long long,int> m1;
#define MAX 100000
vector<bool>prime(MAX,true);
short p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};
inline int64 scan()
    {
        int64 z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }

inline void gen_primes() 
    { 
      int i,j,c=0; 
       for(i=2;i<=(int)sqrt(MAX);i++) 
         if (prime[i]) 
           for(j=i;j*i<MAX;j++) prime[i*j] = false; 
   }

inline int64 mulmod(int64 a, int64 b, int64 mod) {
    int64 res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
inline uint power(uint a, uint n,uint mod)
{
    uint power = a;
    uint64 result = 1;
 
    do
    {
        if (n & 1)
            result = (result * power %mod);
        	power  = (power * power % mod);
        n >>= 1;
    }while (n);
    return result;
}
inline uint64 power(uint64 a, uint64 n,uint64 mod)
{
    uint64 power = a;
    uint64 result = 1;
 
    do
    {
        if (n & 1)
            result = mulmod(result , power ,mod);
        power = mulmod(power , power, mod);
        n >>= 1;
    }while (n);
    return result;
}
 
inline bool witness(uint64 n, uint64 s, uint64 d, uint64 a)
{
    uint64 x = power(a, d, n);
    uint64 y;
 
    do {
        y = mulmod(x , x, n);
        if (y == 1 && x != 1 && x != n-1)
            return false;
        x = y;
        --s;
    }while (s);
    if (y != 1)
        return false;
    return true;
}
inline bool is_prime_mr(int64 n)
{
    if (((!(n & 1)) && n != 2 ) || (n < 2) || (n % 3 == 0 && n != 3))
        return false;
    if (n <= 3)
        return true;
 
    uint64 d = n>>1;
    uint64 s = 1;
    while (!(d & 1)) {
        d>>=1;
        ++s;
    }
 
    if (n < 1373653)
        return witness(n, s, d, 2) && witness(n, s, d, 3);
    if (n < 9080191)
        return witness(n, s, d, 31) && witness(n, s, d, 73);
    if (n < 4759123141LL)
        return witness(n, s, d, 2) && witness(n, s, d, 7) && witness(n, s, d, 61);
    if (n < 1122004669633LL)
        return witness(n, s, d, 2) && witness(n, s, d, 13) && witness(n, s, d, 23) && witness(n, s, d, 1662803);
    if (n < 2152302898747LL)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11);
    if (n < 3474749660383LL)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13);
    return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13) && witness(n, s, d, 17);
}

inline uint64 gcd(uint64 u,uint64 v)
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

inline uint64 brent_pollard_factor(uint64 n)
{
   const int m = 50;
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
         for(int i=0; i < m && i < r-k; i++) {
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
inline void factor(int64 n)
{
	if(n==1)
		return;
	if((n < MAX)&&(prime[n])){m1[n]=1;return;}
	else{
	if(is_prime_mr(n))
	{
		
		m1[n]=1;
		return;
		
	}}
    int64 d=brent_pollard_factor(n);
	factor(d);
	factor(n/d);
}
inline void put_uint64(int n) {
  char stack[20];
  int top = 0;
  if(n == 0) {
    putchar_unlocked('0');
  } else {
    while(n > 0) {
      stack[top++] = n % 10 + '0';
      n /= 10;
    }
    while(top > 0) {
      putchar_unlocked(stack[--top]);
    }
  }
  putchar_unlocked('\n');
}
inline int64 small_f(int64 n)
{   
	int ind=0;
	int64 ret,sq,pp;
	pp=p[0];
	while(n>1 && ind <=50)
	{
		while(n%pp==0)
		{
			m1[pp]=1;
			n/=pp;
			
		}
	ind++;
	if(ind<50)pp=p[ind];
	}
	return n;
}
int main()
{
	int tc;
	int64 n,m;gen_primes();
	tc=scan();
	for(int cs=0;cs<tc;cs++)
	{   
	int64 phi1=1;
		n=scan();
		int v=1;
		if((n < MAX)&&(prime[n]))phi1=(n+1);
		 else{
		unordered_map<long long,int>::iterator it1;
		m=small_f(n);
		factor(m);
		for(it1=m1.begin();it1!=m1.end();it1++)
		{
			
            phi1 *= (it1->first+1);
            phi1 = (phi1>=Mod)?phi1%=Mod:phi1;
             		
		}}
		v=phi1;
		put_uint64(v);
		m1.clear();
	}
	return 0;
}













