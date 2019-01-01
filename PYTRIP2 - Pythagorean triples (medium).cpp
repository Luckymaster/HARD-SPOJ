#include <bits/stdc++.h>
using namespace std;
//https://oeis.org/A101930
int main() {
	
	int N,M,T;
	
	int sum = 0;
	
	cin >> T;
	while(T--){
		cin >> N >> M;
		sum = 0;
		for(int m=2;m*m<=M;++m){
			for(int n=m%2+1; n<=min((int)sqrt(M-m*m),m-1);n+=2){
				if(__gcd(n,m)==1){
					int aux = min(m * m - n * n, 2 * m * n);
					int c = m * m + n * n;
					int prev = (N-1)/aux + 1;
					int next = M/c;
					if(prev<=next)
					sum+=(next - prev + 1);
				}
			}
		}
		cout << sum <<endl;
	}
	return 0;
}
