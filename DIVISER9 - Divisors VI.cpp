#include <bits/stdc++.h>
#define ll long long
#define Mod 1000000007
using namespace std;
#define max 10000003

typedef pair<long long, long long> pii;

vector<int>primes;
void genPrimes(){
	
	vector<bool>isPrime(max+5,1);
	for(int i=2;i*i<=max;i++){
		if(isPrime[i]){
			for(int j=i;j*i<=max;j++)isPrime[i*j]=0;
		}
	}
	primes.push_back(2);
	for(int i=3;i<max;i+=2){
		if(isPrime[i])primes.push_back(i);
	}
	//puts("primegeneration completed");
}

vector<ll> factor(ll n){
	
	vector<ll> ans;
	
	for(int i=0;(ll)primes[i]*primes[i]<=n;i++){
		if(n%primes[i]==0){
			while(n%primes[i]==0){
				ans.push_back(primes[i]);
				n/=primes[i];
			}
		}
	}
	if(n>1)ans.push_back(n);
	//puts("Factorization compled");
	return ans;
}

ll modPow(ll a, ll b, ll mod){
	ll x = 1,y=a;
	if(b==1)return a;
	while(b){
		if(b&1){
			x = x*y%mod;
		}
		y = y*y%mod;
		b>>=1;
	}
	return x;
}
ll solveSingle(ll po,int len){
	set<pii> pq;
	for (int i = 1; i <100; i++){
		ll ppp = modPow(primes[i],po-1,Mod);
		pq.insert(make_pair(ppp, ppp));
	}
	
	ll num=1;
	for(int i=1;i<=len;i++){
		pii top = *pq.begin();
		pq.erase(pq.begin());
	
		ll prime_exp = top.first;
		num = (num * prime_exp) % Mod;
		ll new_base = top.second;
		ll new_prime_exp = prime_exp * prime_exp%Mod;
		pq.insert(pii(new_prime_exp, new_base));
	}
	return num;
}

ll solveGeneral(vector<ll> fct){
	
	ll num = 1;
	reverse(fct.begin(),fct.end());
	for(int i=0;i<fct.size();i++){
		num = num*modPow(primes[i+1],fct[i]-1,Mod);
		num%=Mod;
	}
	return num;
}
int main() {
	int tc;
	ll n,res;
	genPrimes();
	while(cin >> n){
		vector<ll> aux = factor(n);
		
		set<ll>tmp(aux.begin(),aux.end());
		if(tmp.size()==1){
			if(aux[0]==n){
				res = modPow(3,n-1,Mod);
			}else{
				res = solveSingle(aux[0],aux.size());
			}
		}else{
			res = solveGeneral(aux);
		}
		cout << res <<endl;
	}
	return 0;
}
