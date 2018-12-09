#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
#define ull unsigned long long
#define un unsigned
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm.hpp>
vector<ull> allPalinprime;
vector<bool> isPrime(10000000,1);

inline void genPrimes(){
	for(int i=2;i*i<=10000000;i++){
		if(isPrime[i]){
			for(int j=i;i*j<=10000000;j++){
				isPrime[i*j]=0;
			}
		}
	}
}

inline i64 mulmod(i64 a, i64 b, i64 mod) {
    i64 res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
inline un mulmod(un a, un b, un mod) {
    return a*b%mod;
}
inline i64 power(i64 a, i64 n, i64 mod)
{
    i64 power = a;
    i64 result = 1;
 
    do
    {
        if (n & 1)
            result = mulmod(result , power ,mod);
        power = mulmod(power , power, mod);
        n >>= 1;
    }while (n);
    return result;
}
 
// n-1 = 2^s * d with d odd by factoring powers of 2 from n-1
inline bool witness(i64 n, i64 s, i64 d, i64 a)
{
    i64 x = power(a, d, n);
    i64 y;
 
     do{
        y = mulmod(x , x, n);
        if (y == 1 && x != 1 && x != n-1)
            return false;
        x = y;
        --s;
    }while (s);
    if (y != 1)
        return false;
    return true;
}
 
/*
 * if n < 1,373,653, it is enough to test a = 2 and 3;
 * if n < 9,080,191, it is enough to test a = 31 and 73;
 * if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
 * if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
 * if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
 * if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
 * if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
 */
 
bool is_prime_mr(i64 n)
{
	if(n < 10000000){
    	return isPrime[n];
    }
    if (((!(n & 1)) && n != 2 ) || (n < 2) || (n % 3 == 0 && n != 3) || n%5==0 || n%7==0 || n%11==0)
        return false;
    
 
    i64 d = n / 2;
    i64 s = 1;
    while (!(d & 1)) {
        d /= 2;
        ++s;
    }
 
    if (n < 1373653)
        return witness(n, s, d, 2) && witness(n, s, d, 3);
    if (n < 9080191)
        return witness(n, s, d, 31) && witness(n, s, d, 73);
    if (n < 4759123141LL)
        return witness(n, s, d, 2) && witness(n, s, d, 7) && witness(n, s, d, 61);
    if (n < 1122004669633LL)
        return witness(n, s, d, 2) && witness(n, s, d, 13) && witness(n, s, d, 23) && witness(n, s, d, 1662803);
    if (n < 2152302898747LL)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11);
    if (n < 3474749660383LL)
        return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13);
    return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13) && witness(n, s, d, 17);
}
vector<ull> gerPalindrome(int n){
	vector<ull> num;
	string s1 = boost::lexical_cast<std::string>(n);
	string s2 = s1;
	reverse(s2.begin(),s2.end());
	int sz = s2.size();
	if('2'==s1[sz] || '4'==s1[sz] || '6'==s1[sz] || '8'==s1[sz] || '5'==s1[sz]){
		return num;
	}
	for(int i=0;i<=9;i++){
		string s3 = s1+boost::lexical_cast<std::string>(i)+s2;
		num.push_back(atol(s3.c_str()));
	}
	return num;
	
}

void compute(){
	for(int i=1;i<1000000;i++){
		vector<ull> ans = gerPalindrome(i);
		for(int nm = 0;nm<ans.size();nm++){
			if(is_prime_mr(ans[nm])){
				allPalinprime.push_back(ans[nm]);
			}
		}
	}
}
inline ull scan()
{
	ull z=0;char c;
	do{ c=getchar_unlocked(); } while(c<'0');
	for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
	return z;
}
inline void fastWrite(ull a)
{
char snum[20];int i=0;
    do{snum[i++]=a%10+48;a=a/10;}
    while (a);i=i-1;while (i>=0)putchar_unlocked(snum[i--]);putchar_unlocked('\n');
}
int main() {
	allPalinprime.push_back(2);
	allPalinprime.push_back(3);
	allPalinprime.push_back(5);
	allPalinprime.push_back(7);
	allPalinprime.push_back(11);
	genPrimes();
	compute();
	int T;
	ull n;
	cin >> T;
	while(T--){
		n=scan();
		int idx = upper_bound(allPalinprime.begin(),allPalinprime.end(),n)-allPalinprime.begin();
		fastWrite(allPalinprime[idx-1]);
		
	}
}