#include <bits/stdc++.h>
#include <limits.h>
using namespace std;
#define u128 __int128
typedef long long int int64;
#define MAX 10000000
#include<boost/multiprecision/cpp_int.hpp>
#include <boost/unordered_map.hpp>
namespace mp=boost::multiprecision;
vector<bool>isprime(MAX,true);
boost::unordered_map<int64,int>m1;
int64 mulmod(int64 a, int64 b, int64 mod) {
    int64 res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
vector<int>primes;
void genprimes(){
	isprime[1]=isprime[0]=false;
	for(int i=2;i*i<=MAX;i++){
		if(isprime[i]){
			for(int j=i;j*i<=MAX;j++) isprime[i*j]=false;
		}
	}
	for(int i=2;i<1001;i++){
		if(isprime[i])primes.push_back(i);
	}
}
inline int64 power(int64 a, int64 n,int64 mod)
{
    int64 power = a;
    int64 result = 1;
 
    do{
        if (n & 1)
            result = mulmod(result , power ,mod);
        power = mulmod(power , power, mod);
        n >>= 1;
    }while (n);
    return result;
}
 
bool witness(int64 n, int64 s, int64 d, int64 a)
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
bool is_prime(int64 n)
{
	if(n<MAX) return isprime[n];
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

int64 gcd(int64 u,int64 v)
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
int64 pollard_brent(int64 N)
{
	int64 g,r,q,x,ys,i,k,cs,xx;
	if(!(N&1)) return 2;
	int64 y = rand()%(N-1)+1;
	int64 c = rand()%(N-1)+1;
	int64 m = rand()%(N-1)+1;
	g = 1;
	r = 1;
	q = 1;
	do{
		x = y;
		for(i=0; i < r; i++)
		y = (mulmod(y,y,N)+c);
		y>=N?y-=N:y;
		k = 0;
		do{
			ys = y;
			for(i=0;i<min(m,r-k);i++){
				y = (mulmod(y,y,N)+c);
				y>=N?y-=N:y;
				q = mulmod(q,abs(x-y),N);
			}
			g = gcd(q,N);
			k = k+m;
		}while(k < r && g==1);
		r<<= 1;
	}while(g==1);
	if(g==N){
		do{ 
			cs = mulmod(ys,ys,N);
			ys = (cs+c);
			ys>=N?ys-=N:y;
			g = gcd(abs(x-ys),N);
			if(g>1)break;
		}while(true);
	}
	return g;
}
void factor(int64 n){
	if(n==1)
		return;
	if(is_prime(n)){
		m1[n]+=1;
		return;
	}
	int64 d=pollard_brent(n);
	factor(d);
	factor(n/d);
}
inline int64 scan(){
	int64 z=0;
	char c;
	do{ c=getchar_unlocked(); } while(c<'0');
	for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
	return z;
}
void put_uint64(int64 n) {
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
inline void updateit(int64 &divsum,int64 n, unsigned p){
	if(p==1) divsum *= (n+1);
	else divsum *= ((pow(n,p+1)-1)/(n-1));
}
int  smallfactor(int aux){
	for(int i=0;primes[i]*primes[i]*primes[i]<=aux;i++){
		if(aux%primes[i]==0){
			while(aux%primes[i]==0){
				aux/=primes[i];
				m1[primes[i]]+=1;
			}
		}
	}
	if(aux > 1){
	int sq = sqrt(aux);
	int aux1 = aux;
	if(sq*sq==aux){
		m1[sq]+=2;
		aux = 1;
	}
	}
	return aux;
}
int main()
{
	int t;
	long long n,x,y,divsum = 1,divcnt = 1,divcntmax = 0, divsummax = 0;
	genprimes();
		scanf("%lld",&n);
		int num[n+1];
		for(int i=0;i<n;i++){
			cin >> num[i];
		}
		boost::unordered_map<long long,int>::iterator it1;
		sort(num,num + n);
		do{
			int aux = 0;
			divsum = 1;divcnt = 1;
			for(int i=0;i<n;i++)aux = aux*10 + num[i];
			int aux1 =  smallfactor(aux);
			factor(aux1);
			for(it1=m1.begin();it1!=m1.end();it1++){
				divcnt*=(it1->second + 1);
				updateit(divsum,(it1->first),(it1->second));
			}
			if(divsummax < divsum){
				divsummax = divsum;
				x = aux;
			}
			if(divcntmax < divcnt){
				divcntmax = divcnt;
				y = aux;
			}
			m1.clear();
		}while(std::next_permutation(num,num+n));
		cout<<y<<" "<<x<<endl;
	return 0;
}
