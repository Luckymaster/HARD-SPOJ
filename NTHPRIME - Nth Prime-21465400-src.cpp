#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull long long
#define LD long double
double eps=1e-9;
uint *primrange,*p,idx;
vector<uint>prime;

void init(uint l){
	uint MAX = l;
	vector<bool>is(MAX,0);
	p = new uint[MAX+1];primrange=new uint[MAX+1];
	for(ull i=2; i<=MAX; i++) {
		if(!is[i]) {
			for(ull j=i*i; j<=MAX; j+=i)is[j]=1;
			p[++idx]=i;
		}
	primrange[i]=idx;
	}
	for(uint i=1;i<idx&&p[i]<200000;i++)prime.push_back(p[i]);
	is.clear();
}

unordered_map<ull,ull> memo,memo2;
ull phi(ull x, ull a){
  if(a==1 || !x)return (x+1)/2;
  ull &c=memo[(x<<10)+a];if(c)return c;
  return c=phi(x,a-1)-phi(x/p[a],a-1);
}
ull pi(ull n){
  if(n<=40000000){
  	return primrange[n];
  }
  if(memo2[n]) return memo2[n];
  uint a=pi(pow(n,1./4)+eps);
  uint b=pi(sqrt(n)+eps);
  uint c=pi(pow(n,1./3)+eps);
  ull sum=phi(n,a)+(b+a-2)*(b-a+1)/2;
  for(ull i=a+1; i<=b; i++){
    ull w=n/p[i];
    sum-=pi(w);
    if(i<=c) for(ull j=i;j<=pi(sqrt(w)+eps);j++) sum+=j-1-pi(w/p[j]);
  }
  return memo2[n]=sum;
}

ll getLn(ll n){
	return log(n);
}


int main(){
	init(40000000);
	ll n,m;
	cin >> n;
	
	ll l = n * getLn(n) + n*(getLn(getLn(n))-.6);
	
	ll u =  n * getLn(n) + n*(getLn(getLn(n))+.9);
	
	//cout << l << "   " << u <<endl;
	while(l != u){ 
		m = l + (u - l) /2;
		if(pi(m) >= n)u = m;
		else l = m + 1; 
		//cout<<"m = " << m << endl;
	}
	if(n==1)puts("2");
	else if(n==2)puts("3");
	else{
	if(m%2==0)m+=1;
	
	cout << m ;
	}
}