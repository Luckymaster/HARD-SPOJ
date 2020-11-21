#include<bits/stdc++.h>
typedef long long int64;
typedef unsigned long long uint64;
using namespace std;
unsigned prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109};
inline uint scan()
    {
        uint z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }

inline uint power(uint a, uint n,uint mod)
{
    uint power = a;
    uint result = 1;
 
    while (n)
    {
        if (n & 1)
            result = (uint64)result*power%mod;
            power = (uint64)power*power%mod;
        n >>= 1;
    }
    return result;
}

bool witness(uint n, uint s, uint d, uint a)
{
    int64 x = power(a, d, n);
    int64 y;
 
    while (s) {
        y = (x*x%n);
        if (y == 1 && x != 1 && x != n-1)
            return false;
        x = y;
        --s;
    }
    if (y != 1)
        return false;
    return true;
}
bool is_prime_mr(int64 n)
{
    if (((!(n & 1)) && n != 2 ) || (n < 2) || (n % 3 == 0 && n != 3))
        return false;
    if (n <= 3)
        return true;
 
    int64 d = n>>1;
    int64 s = 1;
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
inline short factor_small(uint n)
{  
	uint p=0,c=1,i;
	for(i=0;prime[i]*prime[i]*prime[i]<=n;i++)
	{ 
		if(n%prime[i]==0)
		{  
			p=0;
			while(n%prime[i]==0)
			{
				n/=prime[i];
			   p+=1;
			}
			c*=((p<<1)+1);
		}
	}
	if(n>1)
	{
		uint sq = (uint)sqrt(n);
		if(is_prime_mr(n))c*=3;
		else if(sq*sq==n)c*=5;else c*=9;
	}
	return c;
}

inline void put_uint(short n) {
  char stack[12];
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
	uint tc,a,b;
        uint n;
	scanf("%d",&tc);
	while(tc--)
	{
		n=scan();
		if(!(n&1))n>>=1;
		put_uint(factor_small(n)>>1);
	}
}

