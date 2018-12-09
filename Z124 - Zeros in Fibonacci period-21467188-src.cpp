#include <cstdlib>
#include <cstdio>
#include <bits/stdc++.h>
#include <algorithm>
#include <time.h>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;
int T;
long long n, m, k;
const int MaxN = 1005;

bool mark[MaxN];
unordered_map<long long, long long> pisanoMap,divisor;
typedef long long int int64;
typedef unsigned long long uint64;
typedef long long LL;
typedef long double LD;
#define max_uint64 9223372036854775807ULL
inline int64 mulmod(int64 a, int64 b, int64 mod) {
    int64 res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
inline int64 power(int64 a, int64 n,int64 mod)
{
    int64 power = a;
    int64 result = 1;
 
    while (n)
    {
        if (n & 1)
            result = mulmod(result , power ,mod);
        power = mulmod(power , power, mod);
        n >>= 1;
    }
    return result;
}
int64 a,b;
int64 fibb(int64 n, int64 MM)
{
	if(n==0)
	{
		a=0;b=1;
		return a;
	}
	else
	{
		a=fibb(n>>1,MM);
		int64 c = mulmod(a , (b+b - a+MM) , MM);
		int64 d = mulmod(b,b,MM) + mulmod(a,a,MM);
		if(d>=MM)d-=MM;
		if(n&1){
			a=d;
			b=c+d;
			return a;
		}
		else{
			a=c;
			b=d;
			return a;
		}
	}
}
inline bool witness(int64 n, int64 s, int64 d, int64 a)
{
    int64 x = power(a, d, n);
    int64 y;
 
    while (s) {
        y = mulmod(x , x, n);
        if (y == 1 && x != 1 && x != n-1)
            return false;
        x = y;
        --s;
    }
    if (y != 1)
        return false;
    return true;
}
inline bool is_prime_mr(int64 n)
{
    if(n < MaxN) return mark[n];
	return true;
	
}


inline int64 gcd(int64 u,int64 v)
{
   return __gcd(u,v);
}
inline int64 scan()
    {
        int64 z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void put_uint(int64 n) {
  char stack[22];
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




inline void factor(int64 n, int64 ret[], int& size){
    if (n == 1) return;

    if (is_prime_mr(n)){
		ret[++size] = n;
		divisor[n]++;
        return;
    }

	int64 d = brent_pollard_factor(n);
    factor(d, ret, size);
    factor(n / d, ret, size);
}


int primes[MaxN], pCount = 0;

inline void factorPro(int64 n, int64 ret[], int &size){

    for (int i = 0; n > 1 &&  i < 20; i++) while (n % primes[i] == 0){
        n /= primes[i];
        ret[++size] = primes[i];
    }

    factor(n, ret, size);
}

inline void largefactor(int64 n, int64 p[], int deg[], int& factorNum)
{
	int size = 0;
	p[0] = 0;
	factorPro(n, p, size);
	sort(p + 1, p + size + 1);
	for (int i = 1; i <= size; i++)
	{
		if (p[i] == p[i - 1])
			deg[factorNum]++;
		else
		{
			factorNum++;
			p[factorNum] = p[i];
			deg[factorNum] = 1;
		}
	}
}

int factorNum1;
int64 p1[100];
int deg1[100];


inline long long PisanoPeriodPrime(long long p)
{
	if (p == 2)
		return 3LL;
	if (p == 3)
		return 8LL;
	if (p == 5)
		return 20LL;

	if (pisanoMap.find(p) != pisanoMap.end())
		return pisanoMap[p];

	long long n;
	if (p % 5 == 1 || p % 5 == 4)
		n = p - 1;
	else
		n = (p + 1) * 2;

	factorNum1 = 0;
	largefactor(n, p1, deg1, factorNum1);

	long long fn, fn1;
	for (int i = 1; i <= factorNum1; i++)
	{
		if (i == 1 && (p % 5 == 2 || p % 5 == 3)) continue;
		for (int j = 1; j <= deg1[i]; j++)
		{	
			fibb(n / p1[i], p); fn=a; fn1=b;
			if (fn != 0LL || fn1 != 1LL)
				break;
			else
				n = n / p1[i];
		}
	}

	pisanoMap[p] = n;
	return n;
}

long long tmp[100];
inline long long PisanoPeriod(long long p[], int deg[], int factorNum)
{
	if (factorNum == 0)
		return 1LL;

	for (int i = 1; i <= factorNum; i++)
	{
		tmp[i] = 1LL;
		for (int j = 1; j < deg[i]; j++)
			tmp[i] = tmp[i] * p[i];
		tmp[i] = tmp[i] * PisanoPeriodPrime(p[i]);
	}

	long long ret = tmp[1];
	for (int i = 2; i <= factorNum; i++)
		ret = (ret / gcd(ret, tmp[i])) * tmp[i];

	return ret;
}

unordered_map<long long, int> periodMap;
long long p[100];
int deg[100];


long long pisanoPeriods[10000];
long long solve(int64 m,int k)
{
		if (k > 1)
		{
			pisanoPeriods[0] = m;
			int periodNum = 0;
			for (int i = 1; i < k; i++)
			{
				if (pisanoMap.find(pisanoPeriods[i - 1]) != pisanoMap.end())
					pisanoPeriods[i] = pisanoMap[ pisanoPeriods[i - 1] ];
				else
				{
					int factorNum = 0;
					largefactor(pisanoPeriods[i - 1], p, deg, factorNum);
					pisanoPeriods[i] = PisanoPeriod(p, deg, factorNum);
					pisanoMap[ pisanoPeriods[i - 1] ] = pisanoPeriods[i];
				}
				return (pisanoPeriods[i]);
			}
		}
}

LL twick(LL p){
	LL rem = p%20;
	LL rem40 = p%40;
	
	if(rem == 11 || rem == 19) return 1;else
	if(rem == 3  || rem == 7) return 2;else
	if(rem == 13 || rem == 17) return 4; 
	else{
		int rank = 1;
		LL k=2;
		long long prod = solve(p,k);
		if(rem40 == 21 || rem40 == 29){
			LL num[] ={4};
			for(int i=0;i<1;i++){
			long long aux = fibb(prod/num[i],p);
			if(aux == 0){
				rank = max(num[i],rank*1LL);
				break;
			}
		}
		}else{
		LL num[] ={4,2};
		for(int i=0;i<2;i++){
			long long aux = fibb(prod/num[i],p);
			if(aux == 0){
				rank = max(num[i],rank*1LL);
				break;
			}
		}}
		
		return rank;
	}
}

int main()
{
    for (int i = 2; i < MaxN; i++) mark[i] = true;
    for (int i = 2; i * i < MaxN; i++) if (mark[i])
        for (int j = i * i; j < MaxN; j += i){
            mark[j] = false;
        }

    for (int i = 2; i < MaxN; i++) if (mark[i])
        primes[pCount++] = i;


	scanf("%d", &T);

	for (int t = 0; t < T; t++)
	{
		k=2;
		m=scan();
		if(m==2){
			puts("1");
			continue;
		}
		put_uint(twick(m));
	}
	return 0;
}