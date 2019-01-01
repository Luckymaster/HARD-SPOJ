#include <bits/stdc++.h>
#include <boost/unordered_map.hpp>
#define ull unsigned long long
using namespace std;
unordered_map <ull, ull> S;
ull sum_of_primes(ull N) {
	ull r = (ull)sqrt(N), n = N;
	vector <ull> V;
	ull nv = r + N/r - 1;
	for (ull i=0; i<r; i++) {
		V.push_back(N/(i+1));
	}
	for (ull i=r; i<nv; i++) {
		V.push_back(V.back() - 1);
	}
	for (ull i=0; i<nv; i++) {
		S[V[i]] = V[i] * (V[i] + 1) / 2 - 1;
	}
	for (ull p=2; p<=r; p++) {
		if (S[p] > S[p-1]) {
			ull sp = S[p-1];
			ull p2 = p*p;
			for (ull i=0; i<nv; i++) {
				if (V[i] < p2) break;
				S[V[i]] -= p * (S[V[i]/p] - sp);
			}
		}
	}

	return S[N];
}
int main(){
	ull n;
	cin >> n;
	cout<<sum_of_primes(n)<<endl;
} 
