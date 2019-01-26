/*https://oeis.org/A000031// I just did OEiS and got the answer.
with(numtheory); A000031 := proc(n) local d, s; if n = 0 then RETURN(1); else s := 0; for d in divisors(n) 
do s := s+phi(d)*2^(n/d); od; RETURN(s/n); fi; end; [ seq(A000031(n), n=0..50) ];*/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
#define MOD 1000000007
#define MAXN 10000009
ull phi[MAXN + 1], prime[MAXN/10], sz=0,po2[MAXN];
uint divs[MAXN+1];
vector<bool>mark(MAXN,0);
int b[MAXN];
inline unsigned scan(){
	unsigned z=0;char c;
	do{ c=getchar_unlocked(); } while(c<'0');
	for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
	return z;
}
inline int modInverse(int a, int n) {
	int i = n, v = 0, d = 1;
	while (a>0){
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
int main(){
	ull s= 0;
	phi[1] = 1;b[1]=-1;
	po2[1]=2;
	po2[2]=4;
	for (uint i = 1; ++i <= MAXN;){
		po2[i]=(po2[i-1]<<1)%MOD;
		b[i]=-1;
		if(!mark[i]){
    		phi[i] = i-1;
    		prime[sz++]= i;
    	}
    	for (uint j=0; j<sz && prime[j]*i <= MAXN; j++ ){
    		mark[prime[j]*i]=1;
    		if(i%prime[j]==0){
    			phi[i*prime[j]] = phi[i]*prime[j];break;
    		}
    		else phi[i*prime[j]] = phi[i]*(prime[j]-1);
    	}
    }
    ull aux = 1;
    memset(divs,0,sizeof(divs));
    for (uint i=0;++i< MAXN;){
    	for (int j=i;j < MAXN;j += i){
    		divs[j] = (divs[j] + phi[i] * po2[j/i])%MOD;
    		
    	}
    }
    int tc;
    tc=scan();
    while(tc--){
    	int n;
    	n=scan();
    	printf("%lld\n",divs[n]*1LL*modInverse(n,MOD)%MOD);
    }
   return 0;  
}
