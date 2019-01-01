#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
vector<int> primes;
vector<bool>isPrime(1000001,1);
vector<bool>composit(1000007,false);
void genPrimes(){
	for(int i=2;i*i<=1000000;i++){
		if(isPrime[i]){
			for(int j=i*i;j<=1000000;j+=i){
				isPrime[j]=0;
			}
		}
	}
	for(int i=2;i<=1000000;i+=1){
		if(isPrime[i]){
			primes.push_back(i);
		}else{
			composit[i]=true;
		}
	}
}
inline int scan()
    {
        uint z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
int compute(int set[],int n,int m){
	ull L = 1;
	int s = 0,k;
	int mm = 0;
	vector<int> aux;
	for (int i = 0; i < (1<<n); i++){
		// Print current subset
		for (int j = 0; j < n; j++){
                if ((i & (1 << j)))
                    aux.push_back(set[j]);
		}
		if(aux.size()==1){    
			s+=(m/aux[0] - mm/aux[0]);
		}
		if(aux.size()>1){
			 L=(aux[0]*aux[1])/__gcd(aux[0],aux[1]);
			 for(k=2;k<aux.size();k++)
			 L = L*aux[k]/__gcd(L,aux[k]*1ULL);
			 	if((aux.size())&1)s+=(m/L-mm/L);
                else  s-=(m/L-mm/L);
		}aux.clear();
    }
    return s;
}
int bf(int arr[], int n, int k){
	vector<bool>composit1 = composit;
	int all = 0;
	for(int i=0;i<k;i++){
		for(int j=arr[i];j<=n;j+=arr[i]){
			if(composit1[j]){
				composit1[j]=false;
			}
		}
	}
		//puts("");
	int cnt = 0;
	for(int i=2;i<=n;i++)if(composit1[i]){
		cnt++;
		//	cout<<i<<",";
	}
	return cnt;
	
}

using namespace std;

int main() {
	int t,n,k,ex=0,cs=0;
	genPrimes();
	cin >> t;
	while(t--){
		n=scan();k=scan();
		int arr[k+1];
		int s = 0;
		ex = 0;
		int prm;
		for(int i=0;i<k;i++){
			arr[i]=scan();
		}
		if(n < 10){
			cout <<"Case "<<++cs<<": "<< bf(arr,n,k) <<endl;
		}
		else{
		int lcm = compute(arr,k,n);
		prm =  upper_bound(primes.begin(),primes.end(),n)-primes.begin();
		cout <<"Case "<<++cs<<": "<<(n-lcm - prm + k-1) <<endl;
		}
		
	}
		
	return 0;
}
