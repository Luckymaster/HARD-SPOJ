#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define MAX 1000004
vector<bool>v(MAX);
int len;
uint sp[MAX];
vector<int> gcds[1000005];

inline void Sieve(){
	for (int i = 2; i < MAX; i += 2)	sp[i] = 2;//even numbers have smallest prime factor 2
	for (ull i = 3; i < MAX; i += 2){
		if (!v[i]){
			sp[i] = i;
			for (ull j = i; (j*i) < MAX; j += 2){
				if (!v[j*i])	v[j*i] = 1, sp[j*i] = i;
			}
		}
	}
}
inline void factor(int n){
	int m = n;
	if(n < 2) return;
	do{
		gcds[sp[n]].push_back(m);
		n/=sp[n];
		if(sp[n]==0)break;
    }while(sp[n] && n%sp[n]==0);
	
}
inline int fint()
{
	int ret = 0,j=0;
	char c = getchar_unlocked();
	while (c <= ' ')
	{
		c = getchar_unlocked();
		j++;
	}
		
	do {
		ret = ret * 10 + c - '0';
		c = getchar_unlocked();
	} 
	while (c > ' ');
	return ret;
}
int main() {
	
	Sieve();
	int n ,x,z= 0;
	scanf("%d",&n);
	int ax[n+1];
	int maxAll = -1,one = 0,zero = 0;
	for(int i=0;i<n;i++){
		x = fint();
		ax[i]=x;
		factor(x);
		maxAll = max(x,maxAll);
		if(x == 1)one+=1;
		if(x == 0)zero+=1;
	}
	if(maxAll == 1){
		cout << one <<endl;
		
	}else if(zero == n){
		cout << "2" <<endl;
	}
	else{
	int maxn = 0;
	int idx = 0;
	gcds[2].push_back(2);
	gcds[2].push_back(2);
	vector<int> avPrimes;
	for(int i=0;i<MAX;i++){
		if(gcds[i].size()>0){
			avPrimes.push_back(i);
		}
	}
	long long ansx = 0,ansy=LLONG_MAX,miny=0;
	for(int ip=0;ip<avPrimes.size();ip++){
		for(int j=0;j<n;j++){
			int rem = ax[j]%avPrimes[ip];
			miny += min(avPrimes[ip] -rem , rem );
			if(ansy < miny) break;
		}
		ansy = min(miny,ansy);
		miny  = 0;
	}
	cout <<ansy <<endl;}
	return 0;
}
