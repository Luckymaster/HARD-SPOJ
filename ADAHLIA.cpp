/**
 * Created by Kenneth Chiguichon.
 * Note: Must compile with -std=c++11 or higher flag enabled
 */
#include <bits/stdc++.h>
#include <random>
#include <time.h>
#include <string.h>

using namespace std;
#define u128 __int128
#define ull unsigned long long

void radixSort(int*, int);

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC (clock_t)1000
#endif //CLOCKS_PER_SEC

ull * a;




void radixSort(ull* a, ull N){
    const ull INT_BIT_SIZE = sizeof(ull)<<3, RADIX = 0x100, MASK = RADIX-1, MASK_BIT_LENGTH = 8;
    ull *result = new ull[N](), *buckets = new ull[RADIX](), *startIndex = new ull[RADIX](), *temp = nullptr;
    int flag = 0, key = 0;
    bool hasNeg = false;
    while (flag < INT_BIT_SIZE){
        for (int i = 0; i < N; ++i) {
            key = (a[i] & (MASK << flag)) >> flag;
            if(key < 0){
                key += MASK;
                hasNeg = true;
            }
            ++buckets[key];
        }
        startIndex[0] = 0;
        for (int j = 1; j < RADIX; ++j) startIndex[j] = startIndex[j - 1] + buckets[j - 1];
        for (int i = N-1; i >= 0; --i){
            key = (a[i] & (MASK << flag)) >> flag;
            if(key < 0) key += MASK;
            result[startIndex[key] + --buckets[key]] = a[i];
        }
        memcpy(a,result,N*sizeof(ull));
        flag += MASK_BIT_LENGTH;
    }
    if(hasNeg){
        int indexOfNeg = 0;
        for (int i = 0; i < N; i++) {
            if(a[i] < 0) {
                indexOfNeg = i;
                break;
            }
        }
        memcpy(a,result+indexOfNeg,(N-indexOfNeg)*sizeof(ull));
        memcpy(a+(N-indexOfNeg),result,indexOfNeg*sizeof(ull));
    }
    delete[] result;
    delete[] buckets;
    delete[] startIndex;
}

int main(){
	
	ull T=1,x1,aa,b,n,mod;
	while(T--){
		cin >> n >> aa >> b >> mod;
		a = new ull[n+10];
		cin >> x1;
		unsigned long long sum = 0;
		a[0]=x1;
		for(int i=0;++i<n;){
			u128  aux = 1;
			aux = (a[i-1] * aux * aa + b)%mod;
			a[i] = (ull)aux;
		}
		radixSort(a,n);
		ull diff = 0;
		for(int i=0;++i<n;){
			if (a[i] - a[i - 1] > diff) diff = a[i] - a[i - 1];
		}
		cout << diff <<endl;
	}
}
