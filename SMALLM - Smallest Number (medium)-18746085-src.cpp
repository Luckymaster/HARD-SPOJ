#include <bits/stdc++.h>
#include <new>
using namespace std;
#define u8 unsigned short
#define ull unsigned long long
#define ll long long
#define uint unsigned
#define LD long double
#define DO(P,R,I,M,E,S,i0,v0,i1,v1,i2,v2,i3,v3,i4,v4,i5,v5,i6,v6,i7,v7) k=P;\
if (!(sieve[n] & (1<<R))){\
  e = eos - I*n - M;\
  for (m = sieve + (30*n + E) * n + S; m < e; m += i0)\
  { *m        |= (1<<v0); *(m += i1) |= (1<<v1);\
    *(m +=i2) |= (1<<v2); *(m += i3) |= (1<<v3);\
    *(m +=i4) |= (1<<v4); *(m += i5) |= (1<<v5);\
    *(m +=i6) |= (1<<v6); *(m += i7) |= (1<<v7);\
  }\
  if (m < eos) { *m|=(1<<v0);\
    if ((m += i1) < eos) { *m |= (1<<v1);\
      if ((m += i2) < eos) { *m |= (1<<v2);\
        if ((m += i3) < eos) { *m |= (1<<v3);\
          if ((m += i4) < eos) { *m |= (1<<v4);\
            if ((m += i5) < eos) { *m |= (1<<v5);\
              if ((m += i6) < eos)   *m |= (1<<v6);\
} } } } } } }

char bits[]={1,7,11,13,17,19,23,29};

unsigned * prime;
uint nbprimes;
const unsigned bytes=1+100000011/30; //prems < 1e8
char sieve[bytes];

inline void primesieve(){
  prime = new unsigned[5761459];
  unsigned p,q,r,k=0,n,s;
  char *m,*e,*eos;
  if (bytes > 30) for (k=r=(bytes-1)/30; (q=r/k)<k; k>>=1) k+=q;
  eos=sieve+bytes; s=k+1; *sieve=1;
  for (n = p = q = r = 0; n < s; n++)
  { DO(p++,0,28, 0, 2, 0,p,0,r,1,q,2,k,3,q,4,k,5,q,6,r,7); r++;
    DO(q++,1,24, 6,14, 1,r,5,q,4,p,0,k,7,p,3,q,2,r,6,p,1); r++; q++;
    DO(p-1,2,26, 9,22, 4,q,0,k,6,q,1,k,7,q,3,r,5,p,2,r,4); r++;
    DO(q-1,3,28,12,26, 5,p,5,q,2,p,1,k,7,r,4,p,3,r,0,k,6);
    DO(q+1,4,26,15,34, 9,q,5,p,6,k,0,r,3,p,4,r,7,k,1,p,2); r++;
    DO(p+1,5,28,17,38,12,k,0,q,4,r,2,p,5,r,3,q,7,k,1,q,6); r++; q++;
    DO(q++,6,26,20,46,17,k,5,r,1,p,6,r,2,k,3,p,7,q,0,p,4); r++;
    DO(p++,7,24,23,58,28,r,0,k,7,r,6,q,5,p,4,q,3,p,2,q,1);
  }
  prime[0]=2,prime[1]=3,prime[2]=5;
  nbprimes=3;
  for (p=0; p<bytes && nbprimes<=5761457; p++)
    for (k=0; k<8; k++)
      if (!(sieve[p] & (1<<k))) prime[nbprimes++]=30*p+bits[k];
}
uint pd[12410];
unsigned * pdinv;
uint pdi[2405];
uint pdi2[181];
uint pdi3[181];
uint pd2[2405];
uint pd3[2405];
inline void inv(ull mod){
    pdinv = new unsigned[5761459];
	pdinv[0]=2;
	for(uint i=1;i<nbprimes;++i){
		pdinv[i]=((ull)pdinv[i-1]*prime[i])%mod;
	}
}
inline void inv1(ull mod){
	pd2[0]=4;
	for(uint i=1;i<2401;++i){
		pd2[i]=((ull)pd2[i-1]*prime[i]*prime[i])%mod;
	}
}
inline void inv2(ull mod){
	pd3[0]=8;
	for(uint i=1;i<2401;++i){
		pd3[i]=((ull)pd3[i-1]*prime[i]*prime[i]*prime[i])%mod;
	}
}
inline uint modInv(int a, int n) 
{
	int i = n, v = 0, d = 1;
	while (a>0) {
		int t = i/a, x = a;
		a = i % x;i = x;
		x = d;d = v - t*x;v = x;
	}
	v %= n;
	if (v<0) v = (v+n);
	return v;
}
inline void fast(uint mod){
	for(uint i=0;i<2401;i++){
		pdi[i]=modInv(pdinv[i],mod);
	}
}
inline void fast3(ull mod){
	for(uint i=0;i<180;++i){
		pdi3[i]=modInv(pd3[i],mod);
	}
}
inline void fast1(uint mod){
	for(uint i=0;i<=180;i++){
		pdi2[i]=modInv(pd2[i],mod);
	}
}
inline void primeprod(uint mod){
	pd[0]=16;
	uint xx=0;
	for(uint i=1;prime[i]<=pow(100000001,1./4);++i){
		pd[i]=((ull)pd[i-1]*((ull)(prime[i]*prime[i]*prime[i]*prime[i])%mod)%mod);
	}
}
ull solve_large(uint n,uint mod){
	ull ans=1;
	uint lm = (uint)pow(n,1./5);
	lm++;if(lm*lm*lm*lm*lm>n)lm--;
	for(uint i=0;prime[i]<=lm;++i){
		u8 p = (u8)((log(n*1.0)/log(prime[i]*1.0))+.00000001);
		ans*=pow(prime[i],p-4);
		ans%=mod;
	}
	uint cb = (uint)pow(n,1./4);
	uint cb5 = (uint)pow(n,1./3);
	cb5++;if(cb5*cb5*cb5>n)cb5--;
	cb++;if(cb*cb*cb*cb>n)cb--;
	uint c = upper_bound(prime,prime+nbprimes,n)-prime;
	uint d = upper_bound(prime,prime+(uint)sqrt(nbprimes),(uint)sqrt(n))-prime;
	uint e = upper_bound(prime,prime+(uint)sqrt(nbprimes),cb)-prime;
	uint f = upper_bound(prime,prime+(uint)sqrt(nbprimes),cb5)-prime;
	ans=(ans*pd[e-1])%mod;
	ans=(ans*pd3[f-1])%mod;
	ans=(ans*pdi3[e-1]%mod);
	ans=(ans*pd2[d-1])%mod;
	ans = ans*pdi2[f-1]%mod;
	ans = ans*pdinv[c-1]%mod;
	ans = ans*pdi[d-1]%mod;
	return ans;
	
}
inline unsigned scan()
    {
        unsigned z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void put_uint(unsigned n) {
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
int main(){
	uint t,n, mod;
	primesieve();
	scanf("%u %u",&t,&mod);
	primeprod(mod);
	inv(mod);fast(mod);inv1(mod);fast1(mod);inv2(mod);fast3(mod);
	uint a[20]={1,2,6,12,60,60,420,840,2520,2520,27720,27720,360360,360360,360360,720720,12252240,12252240,232792560,232792560};
	while (t--){
		{
			n=scan();
			if(n < 21){
				printf("%u\n",a[n-1]);
				continue;
			}
			uint res = solve_large(n,mod);
			put_uint(res);
		}
	}
	delete[] prime;
	delete[] pdinv;
	return 0;
}





