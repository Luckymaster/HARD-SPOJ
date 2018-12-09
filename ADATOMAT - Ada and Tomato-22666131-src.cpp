/**
 * Created by Kenneth Chiguichon.
 * Note: Must compile with -std=c++11 or higher flag enabled
 */
#include <iostream>
#include <random>
#include <time.h>
#include <string.h>

using namespace std;
#define mod 1000000007
bool arrayIsSorted(int*,int);
int* randomIntArray(int,int,int,mt19937&);
void printArray(int*,int);
void radixSort(int*, int);

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC (clock_t)1000
#endif //CLOCKS_PER_SEC


bool arrayIsSorted(int* a,int N){
    for (int i = 0; i < N-1; ++i) if (a[i] > a[i + 1]) return false;
    return true;
}


int *randomIntArray(int n, int minNum, int maxNum, mt19937 &seed){
    int* a = new int[n];
    uniform_int_distribution<int> genRand(minNum,maxNum);
    for (int i = 0; i<n; ++i) a[i] = genRand(seed);
    return a;
}

void printArray(int* a, int N){
    cout << "[";
    int i=0;
    while(i < N-1) cout << a[i++] << ", ";
    if(i < N) cout << a[i];
    cout << "]";
}

void radixSort(int* a, int N){
    const int INT_BIT_SIZE = sizeof(int)<<3, RADIX = 0x100, MASK = RADIX-1, MASK_BIT_LENGTH = 8;
    int *result = new int[N](), *buckets = new int[RADIX](), *startIndex = new int[RADIX](), *temp = nullptr;
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
        memcpy(a,result,N*sizeof(int));
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
        memcpy(a,result+indexOfNeg,(N-indexOfNeg)*sizeof(int));
        memcpy(a+(N-indexOfNeg),result,indexOfNeg*sizeof(int));
    }
    delete[] result;
    delete[] buckets;
    delete[] startIndex;
}

int main(){
	
	int T,x1,aa,b,n;
	cin >> T;
	while(T--){
		cin >> n >> aa >> b >> x1;
		int a[n+1];
		unsigned long long sum = 0;
		a[0]=x1;
		for(int i=1;i<n;i++){
			unsigned long long  aux = 1;
			aux = (a[i-1] * aux * aa + b)%mod;
			a[i] = (int)aux;
		}
		radixSort(a,n);
		for(int i=0;i<n;i++){
			unsigned long long  aux = 1;
			aux = aux * a[i] * (i + 1)%mod;
			sum += aux;
			sum>=mod?sum-=mod:sum;
		}
		cout << sum <<endl;
	}
}