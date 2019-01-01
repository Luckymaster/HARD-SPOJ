#include <bits/stdc++.h>
#include <boost/unordered_map.hpp>
using namespace std;
#define MAX 7000004
#define ll unsigned long long
uint divsum[MAX+1]={0};

inline void initDivSum(){
	for(uint i=1;i<=MAX;i++){
		for(int j=i;j<=MAX;j+=i){
			divsum[j]+=1;
		}
	}
	for(int i=2;i<=MAX;i++){
		divsum[i]=divsum[i-1]+divsum[i];
	}
}
boost::unordered_map<ll,ll>smmap;
inline ll D(ll N){
	ll sum = 0, u = sqrtl(N); 
	if(N<=MAX) return divsum[N];
	if(smmap[N]) return smmap[N];
	for(uint K=1;K <= u; K++){
		sum += (N / K); 
	}
	sum = 2*sum-u*u;
	smmap[N]=sum;
	return sum;
}
vector<ll>db;
int main() {
	initDivSum();
	ll n,cs=1;
	while(cin >> n){
		ll sum = 0,prev = n;
		
		for(ll i=1;i*i<=n;i++){
			db.push_back(i);
			db.push_back((ll)floor(n/i));
		}
		sort(db.begin(),db.end());
		for(int i=0;i<db.size();i++){
			ll aux = db[i];
			sum = sum +  (D(prev) - D((ll)floor(n/(aux+1)))) * (aux);
			prev = (ll)(floor(n/(aux+1)));
		}
		cout<<"Case "<<cs++<<": "<<sum<<endl;
		db.clear();
	}
	return 0;
}
