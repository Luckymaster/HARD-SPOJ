//this need FFT, I have no idea how to use fft here. however this algorithm also works fine its takes 3X time than FFT implementation.
#include <bits/stdc++.h>
using namespace std;
#define MAX1 500002
#define MAX 500002


vector<bool> isPrime(MAX+1,1);
vector<uint> primes;
vector<uint>primeMap(MAX+1,0);
vector<uint>primeMap3(MAX+1,0);

inline void genPrimes(){
	
	isPrime[0] = isPrime[1] = 0;
	for(uint i=2;i*i<=MAX; i++){
		if(isPrime[i]){
			for(uint j=i;j*i<=MAX;j++){
				isPrime[i*j] = 0;
			}
		}
	}
	primes.push_back(2);
	for(uint i=3;i<=MAX;i+=2){
		if(isPrime[i]){
			primes.push_back(i);
		}
	}
	
	for(uint i=0;i<primes.size();i++){
		uint lb = upper_bound(primes.begin(),primes.end(),primes[i]) - primes.begin();
		for(uint j = lb ;primes[j]+primes[i]<MAX && j < primes.size();j++){
			primeMap[primes[i] + primes[j]]+=1;
		}
	}
	

	for(uint i=5;i < MAX1;i++){
		if(primeMap[i]){
			uint key = MAX1 - i;
			uint lb = upper_bound(primes.begin(),primes.end(),key) - primes.begin();
			uint p2 = primeMap[i];
			for(uint j=0;j<=lb;j++){
				if(primes[j] <= i && !isPrime[i-primes[j]] )
				primeMap3[i+primes[j]]+=(p2);
				else if(primes[j] < i)
				primeMap3[i+primes[j]]+=(p2-1);
				else
				primeMap3[i+primes[j]]+=(p2);
				
			}
		}
	}
}
inline int scan()
    {
    register int z=0;
    char c;
    do{ c=getchar_unlocked(); } while(c<'0');
    for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
    return z;
 }
 
 inline void put_ull(int n) {
  char stack[44];
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
int main() {
	
	genPrimes();
	
	int n,t,cs = 0;
	t=scan();
	while(t--){
		n=scan();
		if(isPrime[n]){
			printf("1 1\n");
		}else
		if(n > 2 && isPrime[n-2] && n!=4){
			putchar_unlocked('2');
			putchar_unlocked(' ');
			put_ull(primeMap[n]);
		}else
		if(primeMap[n]){
			putchar_unlocked('2');
			putchar_unlocked(' ');
			put_ull(primeMap[n]);
		}else
		if(primeMap3[n]){
			putchar_unlocked('3');
			putchar_unlocked(' ');
			put_ull((primeMap3[n] + 1)/3);
		}else{
			printf("-1 -1\n");
		}
	}
	return 0;
}
