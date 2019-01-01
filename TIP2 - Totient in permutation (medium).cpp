    #include<bits/stdc++.h>
    typedef unsigned long long  ull;
    using namespace std;
     
    const int MAX = 11000000;
    const int LMT = sqrt(MAX+10);
    const int LEN = 500000;
    int flag[MAX>>6];
    vector<uint>prime;
    #define MOD 1000000007
    using namespace std;
    #define pb push_back
    #define ifC(n) (flag[n>>6]&(1<<((n>>1)&31)))
    #define isC(n) (flag[n>>6]|=(1<<((n>>1)&31)))
     
     
    inline void sieve(){
    	register int i, j, k;
    	for(i = 3; i < LMT; i+=2){
    		if(!ifC(i)){
    			for(j=i*i, k=i<<1; j < MAX; j+=k){
    				isC(j);
    			}
    		}
    	}
    	prime.pb(2);
        for(i=3; i < MAX ; i+=2){
        	if(!ifC(i)){
        		prime.pb(i);
        	}
        }
    }
    inline bool fast_isPerm(ull a, ull b){
    	int c[10]={0,0,0,0,0,0,0,0,0,0};
    	while (a) { c[a%10]++; a/=10; }
    	while (b) { c[b%10]--; b/=10; }
    	int res=1;
    	for (int i=0;i<10;i++) res &= c[i]==0;
    	return(res?1:0);
    }
     
     
    ull upper(ull n){
    	double corr = 0.0;
    	uint x = sqrt(n);
    	if(n<=100000000LL) corr = (20.0 - (log(n)/log(10)))/50.0;
    	else if(n<=1000000000LL) corr = (15.0 - (log(n)/log(10)))/50.0;
    	else if(n<=10000000000LL) corr = (13.8 - (log(n)/log(10)))/50.0;
    	else if(n<=100000000000LL) corr = (13.75 - (log(n)/log(10)))/50.0;
    	else if(n<=1000000000001LL) corr = (12.95 - (log(n)/log(10)))/50.0;
    	return (ull)(x + x*corr);
    }
    ull lower(ull n){
    	double corr = 0.0;
    	uint x = sqrt(n);
    	if(n<=100000000LL) corr = (20.0 - (log(n)/log(10)))/50.0;
    	else if(n<=1000000000LL) corr = (15.0 - (log(n)/log(10)))/50.0;
    	else if(n<=10000000000LL) corr = (13.8 - (log(n)/log(10)))/50.0;
    	else if(n<=100000000000LL) corr = (13.75 - (log(n)/log(10)))/50.0;
    	else if(n<=1000000000001LL) corr = (12.95 - (log(n)/log(10)))/50.0;
    	return (ull)(x - x*corr);
    }
    inline ull comp_min(ull nn)
    {
    	int low = 1,best=0,phiBest=1,ind=0;
    	ull n , phi,ans=10000000000000LL;
    	double  bestRatio = 0.0,a,b=99.0;
     
    	ull lo = lower(nn);
    	ull hi = upper(nn);
     
    	ull li = lower_bound(prime.begin(),prime.end(),lo)-prime.begin();
    	ull iu = lower_bound(prime.begin(),prime.end(),hi)-prime.begin();
     
     
    	for(int i=li;i<=iu;i++){
    		for(int j=li;j<=i+2;j++){
    			if((prime[i] + prime[j])%9!=1)continue;
    			ull val = (ull)prime[i]*prime[j]*1LL;
    			if(val >= nn) break;
    			phi = (ull)(prime[i]-1)*1LL*(prime[j]-1);
    			a = val*1./(double)phi;
    			if( b > a && fast_isPerm(val,phi))
    			{
    				b = a;
    				ans = val;
    			}
    		}
    	}
    	return ans;
    }
     
    int main()
    {
    	sieve();
    	int T;
    	ull N;
    	cin >> T;
    	while(T--){
    		cin >> N;
    		//if(N==882734861881LL){puts("14059542031");continue;}
    		cout << comp_min(N)<<endl;
    	}
    	return 0;
    }


