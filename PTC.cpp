#include <bits/stdc++.h>
#include <limits.h>
using namespace std;
typedef long long int int64;
typedef long long unsigned uint64;
typedef long long unsigned ull;
#define max_uint64 9223372036854775807LL
map<uint64,uint>m1;
uint p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103
,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,
229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353
,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,
491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,
641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,
787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,
941,947,953,967,971,977,983,991,997};
inline int64 mulmod(int64 a, int64 b, int64 mod) {
    int64 res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
inline int64 power(uint64 a, uint64 n,uint64 mod)
{
    uint64 power = a;
    uint64 result = 1;
 
    while (n)
    {
        if (n & 1)
            result = mulmod(result , power ,mod);
        power = mulmod(power , power, mod);
        n >>= 1;
    }
    return result;
}
 

inline bool is_prime(ull n,int it=3)
{
	if(n!=2 and !(n&1))
		return false;
	ull s =n-1;
	while(!(s&1))
		s>>=1;
	for(int i=0;i<it;i++)
	{
		ull a = rand()%(n-1)+1,temp=s;
		uint64 mod = power(a,temp,n);
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
inline uint64 brent_pollard_factor(uint64 n)
{
   const int m = 30;
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
         g = __gcd(q, n);
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
 
         g = __gcd((x>ys)?x-ys:ys-x, n);
      } while(g == 1);
   }
 
   return g;
}
void factor(uint64 n)
{
	if(n==1)
		return;

	if(is_prime(n))
	{
		
		m1[n]+=1;
		return;
		
	}
    uint64 d=brent_pollard_factor(n);
	factor(d);
	factor(n/d);
}
inline int64 small_f(int64 n)
{   
	uint ind=0;
	uint64 ret,sq,pp;
	pp=p[0];
	while(n>1 && ind <=80)
	{
		while(n%pp==0)
		{
			m1[pp]+=1;
			n/=pp;
			
		}
	ind++;
	if(ind<80)pp=p[ind];
	}
	return n;
}
inline uint64 scan()
{
	uint64 z=0;
	char c;
	do{ c=getchar_unlocked(); } while(c<'0');
	for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
	return z;
}
void put_uint(uint n) {
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

int main()
{
	int tc;
	uint64 n;
	for(cin >> tc;tc--;)
	{   
		n=scan();
		map<uint64,uint>::iterator it1;
		if(!(n&1))n>>=1;
		uint64  m=small_f(n);if(n)factor(m);
		uint phi1=1;
		
		for(it1=m1.begin();it1!=m1.end();it1++)
		{
			phi1 *= ((it1->second<<1) + 1);
		}
		put_uint(phi1>>1);
		m1.clear();
	}
	return 0;
}
