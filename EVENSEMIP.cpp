#include <bits/stdc++.h>
using namespace std;
#define ull long long
vector<bool>smprime[10000005];
vector<int>primes;
void getPrimes(int lmt){
	int i,j;
	vector<bool>prime(lmt+1,true);
	for(i=2;i<=sqrt(lmt);i++){
		if (prime[i]){
			for(j=i*i;j<=lmt;j+=i) prime[j] = false;
		}
	}
	primes.push_back(2);
	for(int i=3;i<lmt;i+=2)if(prime[i])primes.push_back(i);
} 

void etfs(ull st, ull en){
	int rng = lower_bound(primes.begin(),primes.end(),sqrt(en+1))-primes.begin();
	vector<ull>res;
	for(ull i=st;i<=en;i++)res.push_back(i);
	for(ull i=0;i<rng;i++){
		for (ull j = ((st+(primes[i]-1))/primes[i])*primes[i] *1LL; j <= en; j += primes[i]){
			if(res[j-st] < primes[i] || smprime[j-st].size() > 2)continue;
			smprime[j-st].push_back(1);
			res[j-st] /= primes[i];
			while (res[j-st] > 1 && res[j-st] % primes[i] == 0) {
				res[j-st] /= primes[i]; 
				smprime[j-st].push_back(1);
			}
			
		}
	}
	for(ull j=st;j<=en;++j){
		if(res[j-st]>1) {smprime[j-st].push_back(res[j-st]);}
	}
}

int main()
{
	ull mi,ma;
	int t;
	cin >> t;
	getPrimes(10000001);
	while(t--){
	vector<ull> fans,fans1;
	cin >> mi >> ma;
	ull cnt = 0,maxc = -1,idx;
	for(int i=0;i<ma-mi + 1;i++)smprime[i].clear();
	
	etfs(mi,ma);
	for(ull i= 0;i<ma-mi+1;i++){
		if(smprime[i].size() == 2 ){
			if((i + mi)%2==0 ){
				fans.push_back((i + mi));
				cnt++;
			}
			else if( maxc < cnt ){
					maxc = cnt;
					fans1.clear();
					for(int k=0;k<fans.size();k++)fans1.push_back(fans[k]);
					fans.clear();
					cnt = 0;
			}else{
					fans.clear();
					cnt = 0;
			}
		}
					
	}
	if(fans.size() > fans1.size()){
		cout << fans.size() << endl;
		for(int k=0;k<fans.size();k++) cout << fans[k]<<" ";cout<<endl;
	}else{
		cout << fans1.size() << endl;
		for(int k=0;k<fans1.size();k++) cout << fans1[k]<<" ";cout<<endl;
	}
	}

}
