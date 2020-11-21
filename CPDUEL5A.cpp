//C*(E+1)^2 = x
//x/c  should be prefect square

#include <bits/stdc++.h>
using namespace std;
int getA(int e,int c){
	return c*e - e;
}

int getB(int e,int c){
	return c*e + e;
}

int getD(int e,int c){
	return e*e*c;
}

bool pSquare(int num)
{
	int r=(int)sqrt(num);
	if(r*r==num)
	return true;
	return false;
}
inline int scan()
    {
    register int z=0;
    char c;
    do{ c=getchar_unlocked(); } while(c<'0');
    for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
    return z;
    }
vector<int> getDivisors(int n){
	vector<int> div;
	int v =1;
	if(n&1) v = 2;
	for(int i=1;i*i<=n;i=i+v){
		if(n%i==0){
			div.push_back(i);
			if(i!=n/i){
				div.push_back(n/i);
			}
		}
	}
	sort(div.begin(),div.end());
	return div;
}
int main() {
	int t,x;
	t=scan();
	for(int cs=1;cs<=t;cs++){
		
		x=scan();
		int m = x;
		bool com = false;
		vector<int> div = getDivisors(x);
		for(int i=0;i<div.size();i++){
			int C = div[i];
			
			if(pSquare(m/C)){
				
				int E = sqrt(m/C) - 1;
				int A = getA(E,C);
				int B = getB(E,C);
				int D = getD(E,C);
				
				int aux = A + B + C + D;
				int BME = B - E;
				int APE = A + E;
				
				if(A && B && D && E && (BME == APE) && (APE == C*E) && (aux == x)){
					com = true;
					break;
				}
				
			}
		}
		printf("%s\n",com?"YES":"NO");
	}
	return 0;
}
