#include <bits/stdc++.h>
using namespace std;

using ull = __int128;
ull * cntA;
ull * cntB;
ull * sumA;
ull * sumB;

inline ull getDv(ull n){
	return (n * n + n)/2 - 1;
}

inline ull fastAmazingPS(ull N){
	ull root = (ull)(sqrt(float(N)));
	vector<bool>u(root+1,false);
	cntA=new ull[root+1];
	cntB=new ull[root+1];
	sumA=new ull[root+1];
	sumB=new ull[root+1];
	ull pcnt = 0,psum = 0,ret = 0,interval = 0,finish = 0,d,q,t;
	for(ull i=1;i<=root;i++){
		cntA[i] = i-1;
	 	sumA[i] = getDv(i);
	 	cntB[i] = N / i - 1;
	 	sumB[i] = getDv(N / i);
	 }
	 for(ull i=2;i<=root;i++){
	 	if(cntA[i] == cntA[i-1]){
	 		continue;
	 	}
	 	pcnt = cntA[i - 1];
	 	psum = sumA[i - 1];
	 	q = i * i;
	 	ret = ret + i * (cntB[i] - pcnt);
	 	cntB[1] = cntB[1] - cntB[i] + pcnt;
	 	sumB[1] = sumB[1] - (sumB[i] - psum) * i;
	 	interval = (i & 1) + 1;
	 	finish = min(root,N / q);
	 	for(ull j=i+interval;j<=finish;j+=interval){
	 		if(u[j])continue;
	 		d = i*j;
	 		if(d<=root){
	 			cntB[j] = cntB[j] - cntB[d] + pcnt;
	 			sumB[j] = sumB[j] - (sumB[d] - psum) * i;
	 		}else{
	 			t = N / d;
	 			cntB[j] = cntB[j] - cntA[t] + pcnt;
	 			sumB[j] = sumB[j] - (sumA[t] - psum) * i;
	 		}
	 	}
	 	if(q <= root){
	 		for(ull k=q; k<=finish-1; k+=i*interval){
	 			u[k] = true;
	 		}
	 	}
	 	for(ull l=root;l>=q-1;l--){
	 		t = l/i;
	 		cntA[l] = cntA[l] - cntA[t] + pcnt;
	 		sumA[l] = sumA[l] - (sumA[t] - psum) * i;
	 	}
	 }
	 return (sumB[1] + ret);
}
inline ull scan(){
	ull z=0;char c;
	do{ c=getchar_unlocked(); } while(c<'0');
	for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);return z;
}
inline void fastWrite(ull a){
	char snum[20];
	int i=0;
	do{
		snum[i++]=a%10+48;
		a=a/10;
	}while (a);
	i=i-1;
	while (i>=0)
	putchar_unlocked(snum[i--]);
	putchar_unlocked('\n');
}
int main() {
  int T;
  cin >> T;
  ull mod = 1;
  int maxm = 1;
  while(maxm<=64){
  	mod<<=1;
  	maxm++;
  }
  for (int i = 1; i <= T; ++i) {
    ull n;
    n = scan();
    fastWrite(fastAmazingPS(n)%mod);
  }
  return 0;
}
