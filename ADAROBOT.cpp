#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define MAX 200000000
ull bit_1[MAX+1];
ull bitPow[65];
const int lsb_64_table[64] =
{
   63, 30,  3, 32, 59, 14, 11, 33,
   60, 24, 50,  9, 55, 19, 21, 34,
   61, 29,  2, 53, 51, 23, 41, 18,
   56, 28,  1, 43, 46, 27,  0, 35,
   62, 31, 58,  4,  5, 49, 54,  6,
   15, 52, 12, 40,  7, 42, 45, 16,
   25, 57, 48, 13, 10, 39,  8, 44,
   20, 47, 38, 22, 17, 37, 36, 26
};
ull bitScanForward(ull bb) {
	unsigned int folded;
	bb ^= bb - 1;
	folded = (int) bb ^ (bb >> 32);
	return lsb_64_table[folded * 0x78291ACF >> 26] + 1;
}
inline int scan()
    {
        uint z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
    
inline void put_uint64(ull n) {
  char stack[20];
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
	bit_1[0]=0;
	bit_1[1]=1;
	for(int i=2;i<65;i++){
		bitPow[i]=powl(i,3);
	}
	for(uint i=2;i<=200000000;i+=2){
		bit_1[i]=bitPow[bitScanForward(i*1ULL*(i-1))] +  bit_1[i-2];
	}
	cin >> t;
	while(t--){
		ull x;
		x = scan();
		put_uint64(bit_1[x]);
	}
	return 0;
}
