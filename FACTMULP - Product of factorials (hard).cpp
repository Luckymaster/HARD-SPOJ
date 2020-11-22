#include <bits/stdc++.h>
#define ULL __int128
#define M 1000000007
using namespace std;

ULL mulmod(ULL a, ULL b, ULL mod) {
    return a*b%mod;
}
ULL modpow(ULL n,ULL k,ULL MOD){
    ULL res=1;
    while(k){
        if(k&1){
            res=mulmod(res,n,MOD);
        }
        n=mulmod(n,n,MOD);
        k>>=1;
    }
    return res%MOD;
}
ULL modInverse(ULL a, ULL n) {
ULL i = n, v = 0, d = 1;
 while (a>0) {
  ULL t = i/a, x = a;
  a = i % x;
  i = x;
  x = d;
  d = v - t*x;
  v = x;
 }
 v %= n;
 if (v<0) v = (v+n)%n;
 return v;
}

ULL modulo (ULL a, ULL b) 
{ 
	return a >= 0 ? a % b : ( b - abs ( a%b ) ) % b; 
}

ULL solve(ULL p,ULL e,ULL mod)
{
	ULL powr,V,exp,n,nn,N,invf,pk;
	ULL inv2=modInverse(2,mod);
        exp =  modpow(p,e-1,mod);
        n =    mulmod(exp,p,mod);
        nn =   mulmod(n,n,mod);
        powr = mulmod(p,(p-1),mod);
        powr = mulmod(powr,inv2,mod);
        V =   (1 + mulmod(mulmod(exp,powr,mod),e,mod))%mod; 
        V =   (2 * V )%mod;
        N =   modulo((nn + n - V + mod)%mod , 2*mod);
        pk =  2 * (p-1);
        invf =  modInverse(pk,mod);
	return mulmod(N ,invf,mod);
}
ULL scan()
    {
    register ULL z=0;
    char c;
    do{ c=getchar_unlocked(); } while(c<'0');
    for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
    return z;
    }
inline void put_ull(__uint128_t n) {
  char stack[44];
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
	ULL p,e;
	scanf("%d",&tc);
	while(tc--){
		p=scan();
		e=scan();
		if(e==0){
			puts("0");
			continue;
		}
		if((p-1)%M ==0 && p == e){
			puts("1");
			continue;
		}
		if((p-1)%M ==0 && p!=e){
			put_ull(e%M);
			continue;
		}
	put_ull(solve(p,e,M));}
	return 0;
}
