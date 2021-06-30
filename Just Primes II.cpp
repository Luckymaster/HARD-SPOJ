#include <bits/stdc++.h>
using namespace std;
#define ll long long
using cd = complex<double>;
const double PI = acos(-1);
const double eps = 1e-3;
const int MAX = 500001;

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real() + eps);
    return result;
}

vector<bool>prime(MAX,1);
vector<ll> primes;
inline int scan()
    {
    register int z=0;
    char c;
    do{ c=getchar_unlocked(); } while(c<'0');
    for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
    return z;
 }
int main(){
	int t ,n;
	prime[0] = prime[1] = 0;
    for(int i=2;i*i<=MAX;i++){
    	if(prime[i]){
    		for(int j=i;j*i<MAX;j++) prime[i*j] = 0;
    	}
    }
    vector<ll> a(MAX,0);
    vector<ll> bb(MAX,0);
    for(int i=0;i<MAX;i++){
    	a[i] = prime[i];
    }
    for(int i=0;i<MAX/2;i++){
    	bb[2*i] = prime[i];
    }
    vector<ll> res = multiply(a,a);
    for(int i=0;i<res.size();i++){res[i]/=2;}
    vector<ll> res1 = multiply(res,a);
    vector<ll> res2 = multiply(bb,a);
	t = scan();
	for(int cs = 1; cs <= t; cs++){
		n = scan();
		if(prime[n]){
			printf("1 1\n");
		}else 
		if(res[n]!=0){
			printf("2 %d\n",res[n]);
		}else 
		if(res1[n]){
			printf("3 %d\n", (res1[n]-res2[n] + 1)/3);
		}else{
			printf("-1 -1\n");
		}
	}
}
