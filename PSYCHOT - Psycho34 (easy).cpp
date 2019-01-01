#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>
#include<cstdio>
int numPrime=155;
using namespace std;
typedef long long uint64;
typedef unsigned long long int64;
int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};

inline int64 mulmod(uint64 a, uint64 b, uint64 mod) {
    uint64 res = (a * ((long double) b / (long double) mod));
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
 
bool is_prime_mr(int64 n)
{
 if(power(2,n-1,n)>1 || power(3,n-1,n)>1 || n==1)
   return false;
 return true;
 }
inline long long scan()
    {
        long long z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }

bool factor(int64 n)
{   
	int power=0,k=0,i,odd=0,even=0,ind=0;
	int64 ret,sq,p;
	p=prime[0];
	while(n>1 && ind <=numPrime)
	{
	    	power=0;
		while(n%p==0)
		{
			power++;
			n/=p;
			
		}
	if(power&1)odd+=1;
	else if(power > 0)even+=1;
	ind++;
	if(ind<numPrime)p=prime[ind];
	}
	if(n>1)
	{
	        sq = (int)sqrt(n);
		if(is_prime_mr(n))odd+=1;
		else if(sq*sq==n)even+=1;
		else {odd+=2;}
	}
	return (even > odd)?true:false;
}
int main() 
{
	int tc;
	int64 n;
	scanf("%d",&tc);
	while(tc--)
	{   
		n=scan();
		if(is_prime_mr(n))puts("Ordinary Number");
		else
		{
			if(factor(n))puts("Psycho Number");
		     else puts("Ordinary Number");
		}
	}
	return 0;
}
