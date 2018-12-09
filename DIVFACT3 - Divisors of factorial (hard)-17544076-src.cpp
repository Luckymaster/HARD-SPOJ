#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define uint unsigned
#define ll long long
#define i64 long long int
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

uint* prime;
unsigned nbprimes;
const unsigned bytes=1+100007011/30; //prems < 1e9
char sieve[bytes];
uint pr[100000001]={0};
inline void primesieve(){
  prime = new uint[5761459];
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
bool zero = false;
inline unsigned multiplicity(unsigned n, unsigned p) {
    unsigned q = n;
    unsigned m = 0;
    do {
        q /= p;
        m += q;
    }while (q >= p);
    return m;
}

inline unsigned modPow(unsigned a, unsigned b,unsigned mod)
{
	uint x = 1,y=a;
	do
	{
		if(b&1) x = ((ull)x*y%mod);
		y = ((ull)y*y%mod);
		b>>=1;
	}while(b);
	return x;
}
unsigned d[2004];
int range;
uint bound(uint n){
	if(pr[n]) return pr[n];
	else{
		uint l = lower_bound(prime,prime+nbprimes,n)-prime;
		pr[n]=l;
		return l;
	}
}
inline unsigned find_pow(unsigned n)
{
	unsigned next=0;
	unsigned prev = bound(n+1);
	for(unsigned i=2;i<range;i++){
		 next = bound(n/i+1);
		 d[i]=(prev-next);
		 prev = next;
	}
	return next;
}
inline uint scan()
    {
        uint z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void put_uint(unsigned n) {
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
int main() {
	primesieve();
	unsigned tc,n,mod,k3=0;
	ull divv = 1;
	//freopen("C:\\Users\\Lakshman\\Desktop\\inpu.txt", "r", stdin);
    //freopen("C:\\Users\\Lakshman\\Desktop\\inpuout.txt", "w", stdout);
	for(scanf("%u",&tc);tc--;){
		divv = 1;
		n=scan();mod=scan();
		if(n < 10000000) range =200;
		else range = 870;
		unsigned limit = find_pow(n);
		for(unsigned i=0;i<limit;i++){
			unsigned k = (multiplicity(n,prime[i]) + 1);
			divv = (divv*k%mod);
		}
		
		for(unsigned x=2;x<range;x++){
			if(d[x])divv=divv*modPow(x,d[x],mod)%mod;
		}
		put_uint(divv);
	}delete[] prime;
	return 0;
}
