#include <bits/stdc++.h>
using namespace std;
vector<int>primes;
#define MAX 100000

void genprimes(){
	vector<bool>isPrime(MAX , true);
	for(int i=2;i*i<=MAX;i++){
		if(isPrime[i]){
			for(int j=i;i*j<=MAX;j++)isPrime[i*j]=false;
		}
	}
	primes.push_back(2);
	for(int i=3;i<=MAX;i+=2){
		if(isPrime[i]){
			primes.push_back(i);
		}
	}
}
inline unsigned fi(unsigned n) {
	unsigned i, result = n; 
	for(i=0;primes[i]*primes[i] <= n;i++) { 
		if (n %primes[i] == 0) result -= result /primes[i]; 
		while (n %primes[i] == 0) n /= primes[i]; 
	} 
	if (n > 1) result -= result / n; 
		return result; 
}
inline int modInverse(int a, int n) 
{
	int i = n, v = 0, d = 1;
	while (a>0) 
	{
		int t = i/a, x = a;
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
int modpow(long long n,int k,int MOD)
{
    long long  res=1;
    while(k)
    {
        if(k&1){
            res=(res*n%MOD);
        }
        n=(n*n%MOD);
        k>>=1;
    }
    return res;
}
inline unsigned scan()
    {
        unsigned z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void put_uint(unsigned  n) {
  char stack[12];
  short top = 0;
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
	int n,e,c,t;
	genprimes();
	t=scan();
	while(t--){
		n=scan();
		e=scan();
		c=scan();
		int phi = fi(n);
		int d = modInverse(e,phi);
		int m = modpow(c,d,n);
		put_uint(m);
	}
	return 0;
}
