#include <bits/stdc++.h>
typedef long long i64;
#define ull unsigned long long
#define un unsigned
using namespace std;
int pn[] = {2,3,5,7};

inline i64 mulmod(i64 a, i64 b, i64 mod) {
    i64 res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
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
 
// n−1 = 2^s * d with d odd by factoring powers of 2 from n−1
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
ull getUll(string s){
	stringstream to_long(s);
	long long x = 0;
	to_long >> x;
	return x;
}
bool is_prime_mr(ull n){
	
    if ((!(n & 1))  || (n < 2) || (n % 3 == 0 && n != 3))
        return false;
    
    ull d = n / 2;
    ull s = 1;
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
    return witness(n, s, d, 2) && witness(n, s, d, 3) && witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11) && witness(n, s, d, 13) && witness(n, s, d, 17) && witness(n, s, d, 19) && witness(n, s, d, 23) && witness(n, s, d, 29);
}
bool isPrime(char c)
{
	return (c == '2' || c == '3' || c == '5' || c == '7');
}
void decrease(string& s, int i)
{
	if (s[i] <= '2') {
		s.erase(i, 1);
		s[i] = '7';
	}

	else if (s[i] == '3')
		s[i] = '2';
	else if (s[i] <= '5')
		s[i] = '3';
	else if (s[i] <= '7')
		s[i] = '5';
	else
		s[i] = '7';

	return;
}

string primeNumberWithPrimeDigits(string s)
{
	for (int i = 0; i < s.length(); i++) {
		if (!isPrime(s[i])) {
			while (s[i] <= '2' && i >= 0)
				i--;
			if (i < 0) {
				i = 0;
				decrease(s, i);
			}
			else
				decrease(s, i);
			for (int j = i + 1; j < s.length(); j++)
				s[j] = '7';		

			break;
		}
	}

	return s;
}
int main()
{
	int t,cs=0;
	string n;
	ull ans = 0,tmp = 0;
	cin >> t;
	while(t--){
		cin >> n;
		ull aux = getUll(n);
		if(aux < 11){
			if(aux  < 2) tmp = 0;
			else if(aux == 2) tmp = 2;
			else if(aux <= 4) tmp = 3;
			else if(aux <= 6) tmp = 5;
			else if(aux <= 10) tmp = 7;
			cout <<"Case " <<++cs<<": "<< tmp<<endl;
			continue;
		}
		while(1){
			ans = getUll(primeNumberWithPrimeDigits(n));
			if(is_prime_mr(ans)){
				break;
			}else{
				ans--;
				n = std::to_string(ans);
			}
		}
		cout <<"Case " <<++cs<<": "<< ans<<endl;
	}
}
