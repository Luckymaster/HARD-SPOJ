#include <bits/stdc++.h>
#include <boost/unordered_map.hpp>
using namespace std;
typedef long long int int64;
typedef unsigned long long  ll;



#define MOD 1000000007
using uint64 = unsigned long long;
using uint32 = unsigned int;
 
const uint32 S = 1e7 + 10;
const uint32 N = 3e7+ 11;
const uint32 M = 1e4;

int mu[N], sigma[N], e[N];
uint32 ps[M];
boost::unordered_map<ll,ll>D2,D1;
void pre_compute(uint32 n) {
  mu[1] = sigma[1] = 1;
  
  for (uint32 i = 2, m = 0; i <= n; ++i) {
    if (!sigma[i]) {
      sigma[i] = e[i] = 2;
      mu[i] = -1;
      if ((uint64)i * i <= n) ps[m++] = i;
    }
    for (uint32 j = 0, u = n / i; j < m && ps[j] <= u; ++j) {
      int p = ps[j], v = p * i;
      if (i % p == 0) {
        mu[v] = 0;
        e[v] = e[i] + 1;
        sigma[v] = sigma[i] / e[i] * e[v];
        break;
      } else {
        e[v] = 2;
        mu[v] = -mu[i];
        sigma[v] = sigma[i] * 2;
      }
    }
  }
  for (uint32 i = 1; i <= n; ++i) {
    sigma[i] += sigma[i - 1];
  }
}

inline ll D(ll N){
	if(N<30000000) return sigma[N];
	if(D1[N]) return D1[N];
	ll sum = 0, u = sqrtl(N); 
	for(uint K=1;K <= u; K++){
		sum += (N / K); 
	}
	sum = 2*sum-u*u;
	D1[N]=sum;
	return sum;
}
inline ll D_Brute_Force(ll n){
	vector<ll>nums;
	ll sum = 0,prev=n;
	for(ll i=1;i*i<=n;i++){
		nums.push_back(i);
		nums.push_back(n/i);
	}
	sort(nums.begin(),nums.end());
	for(int i=0;i<nums.size();i++){
		ll aux = nums[i],next = n/(aux+1);
		sum = sum +  (prev - next) * D(aux);
		prev = next;
	}
	return sum;
}
int main()
{
    pre_compute(30000001);
   int tc;
    scanf ("%d", &tc);
    while (tc--){
        int64 n;
        scanf("%lld",&n);
        int m = (int)sqrt(n);
        int64 res = 0;
        for(int64 i=1;i*i<=n;i++){
        	res += mu[i] * D_Brute_Force(n / (i*i));
        }
        printf("%lld\n",abs(res));
    }
    return 0;
}
