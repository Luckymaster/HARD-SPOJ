#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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
	for(uint i=1;i<idx&&p[i]<500000;i++)prime.push_back(p[i]);
	is.clear();
}

unordered_map<ull,ull> memo,memo2;
ull phi(ull x, ull a){
  if(a==1 || !x)return (x+1)/2;
  ull &c=memo[(x<<10)+a];if(c)return c;
  return c=phi(x,a-1)-phi(x/p[a],a-1);
}
ull pi(ull n){
  if(n<=50000000){
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
ull multiplicity(ull n, ull p) {
    ull q = n;
    ull m = 0;
    do {
        q /= p;
        m += q;
    }while (q >= p);
    return m;
}
ll mulmod(ll a, ll b, ll mod) {
    ll res = (a * ((LD) b / (LD) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
ll modPow(ll a, ll b,ll mod)
{
	ll x = 1,y=a%mod;
	do
	{
		if(b&1) x = mulmod(x, y,mod);
		y = mulmod(y ,y ,mod);
		b>>=1;
	}while(b);
	return x;
}

int main()
{
	
	int t;
	cin >> t;
	ull max = 0;
	ull n,mod;
	ull divv=1;
	vector<pair<ull,ull> > input;
	while(t--)
	{

		cin >> n >> mod;
		max = std::max(max,n); 
		input.push_back(make_pair(n,mod));
	}
	if(max < 10001){
		init(10001);
		vector< pair<ull,ull> >::iterator it;
		for(it=input.begin();it!=input.end();it++){
			divv = 1;
			ull m = it->first;
			ull MOD = it->second;
			for(int i=0;prime[i]<=m;i++){
				divv=mulmod(divv,multiplicity(m,prime[i])+1,MOD);
			}
			cout<<(divv+MOD)%MOD<<endl;
		}input.clear();
	}
	else{
		init(50000000);
		vector< pair<ull,ull> >::iterator it;
		for(it=input.begin();it!=input.end();it++){
			divv=1;
			n = it->first;mod = it->second;
			ll lmt=sqrtl(n);
			for(int i=0;prime[i]<=lmt;i++){
				divv=mulmod(divv,multiplicity(n,prime[i])+1,mod);
			}
			ll aux=n/(lmt+1),x;
			while(aux){
				ll a=((n/aux)-1)/2;
				ll b=((n/(aux+1))-1)/2;
				a=2*a+1; b=2*b+1;if(a==1) a+=1;if(b==1) b+=1;x=pi(a)-pi(b);
				divv = mulmod(divv,modPow(aux+1,x,mod),mod);aux-=1;
			}
			printf("%lld\n",(divv+mod)%mod);
		}input.clear();
	}delete[]p;delete[]primrange;prime.clear();
}
