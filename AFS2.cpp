#include <bits/stdc++.h>
#define u128 __int128
#define ull unsigned long long
using namespace std;


u128 SOD(ull N){
	ull D = 1,Q = N;
	u128 S = 0,ONE = 1;
	while(D<Q){
		S = S + (ONE*Q*(Q+1+(D*2))/2);
		D+=1;
		Q=N/D;
	}
	S = S + (ONE*Q*(Q+1)/2);
	S = S - (ONE*D*D*(D-1)/2);
	return S-(ONE*N*(N+1)>>1);
	
}
inline void put_ull(u128 n) {
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
	int t;
	ull N;
	cin >> t;
	while(t--){
		cin >> N;
		put_ull(SOD(N));
	}
	return 0;
}
