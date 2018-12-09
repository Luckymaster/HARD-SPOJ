#include <bits/stdc++.h>
#include<algorithm>
#include<math.h>
#include<vector>
using namespace std;
#define uint unsigned
#define MAX 100000007
#define MAX1 10006
uint INVDIV[MAX];
vector<int>p;
vector<bool>is(MAX1,true);
void genPrime(){
	for(int i=2;i<=sqrt(MAX1);i++){
		if(is[i]){
			for(int j=i;i*j<MAX1;j++)is[i*j]=false;
		}
	}
	for(int j=2;j<9960;j++)if(is[j])p.push_back(j);
}
struct T{
  uint num;
  uint divsum;
};
T V[MAX+5];
inline unsigned scan(){
	unsigned z=0;char c;
	do{ c=getchar_unlocked(); } while(c<'0');
	for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
	return z;
}
inline void cmpt(){
	for(int i=0;i<MAX;i++){
		V[i].divsum=1;
		V[i].num=i;
	}is[0]=is[1]=false;
	for(uint i=0;i<p.size();i++){
		for(uint j=p[i];j<MAX;j+=p[i]){
		
			uint xx = V[j].num,c = 1;
			if(xx < MAX1 && is[xx])continue;
			do{
				xx/=p[i];
				c=c*p[i]+1;
			}while(xx%p[i]==0);
		V[j].divsum*=c;
		V[j].num=xx;
		}
	}
	for(uint i=2;i<MAX;i++){
		if(V[i].num>1){
			V[i].divsum*=V[i].num+1;
		}
	}
    for(uint i=2;i<MAX;i++){
    	if(V[i].divsum<MAX)
    	if(INVDIV[V[i].divsum]==0){
    		INVDIV[V[i].divsum]=i;
    	}
    }
}
int main() {
	genPrime();
	cmpt();
    int n,tc;
    scanf("%d",&tc);
    INVDIV[1]=1;
    while(tc--){
               n=scan();
               printf("%d\n",INVDIV[n]?INVDIV[n]:-1);
    }
	return 0;
}

































