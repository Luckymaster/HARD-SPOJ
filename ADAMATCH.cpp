#include <bits/stdc++.h>
using namespace std;
#define ll long long
using cd = complex<double>;
const double PI = acos(-1);
const int MAX = 500001;
int possibleCandidates[2*MAX];
const double eps = 1e-3;
string BASE = "ACTG";

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

vector<cd> multiply(vector<int> const& a, vector<int> const& b) {
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

    return fa;
}

int main(){
	
	char MS[MAX];
	char SS[MAX];
	scanf("%s %s", MS,SS);
	int msLen = 0;
	int ssLen = 0;
	
	for(int i=0;i<4;i++){
		msLen = strlen(MS);
		ssLen = strlen(SS);
		vector<int> ams(msLen);
		vector<int> bss(ssLen);
		for (int j = 0; j < msLen; j++) {
			ams[j] = (MS[j]== BASE[i]) ? 1 : 0;
		}
		for (int j = ssLen - 1; j >= 0; j--) {
			bss[ssLen - 1 - j] = (SS[j]== BASE[i]) ? 1 : 0;
		}
		vector<cd> response = multiply(ams, bss);

		for (int j = 0; j < msLen; j++) {
			possibleCandidates[j + ssLen - 1] += (int)(response[j + ssLen - 1].real() + eps);
		}
		ams.clear();
		bss.clear();
	}
	int maxAns = -1;
	for (int i = ssLen - 1; i < msLen; i++) {
		maxAns = max(maxAns, possibleCandidates[i]);
	}
	cout << ssLen - maxAns <<endl;
}
