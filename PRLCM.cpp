#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001
#define MOD 998244353
#define ull long long
int cnt[MAX+1];
ull lsum[MAX + 1];
ull dp[MAX + 10];

ull mulmod(ull a, ull b) {
    ull res = (a * ((long double) b / (long double) MOD));
    res = a * b - res * MOD;
    if (res >= MOD) res -= MOD;
    if (res < 0) res += MOD;
    return res;
}

long long bf(int arr [],int n){
	long long sum = 0;
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
		sum = sum + mulmod(mulmod(arr[i] , arr [j]) , dp[__gcd(arr[i],arr[j])]);
		sum%=MOD;
		}
	}
	return sum%MOD;
}
void modularInverse(){
    dp[0] = dp[1] = 1;
    ull x = 1;
    for (int i = 2; i <= MAX + 1; i++){
        dp[i] = (dp[MOD % i] * (MOD - MOD / i))%MOD;
    }
}
int main() {
	modularInverse();
	int n,x;
	cin >> n;
	int nums[n + 1];
	for(int i=0;i<n;i++){
		cin >> nums[i];
		cnt[nums[i]]++;
	}
	ull maxSum = 0;
	for(int i=1;i<MAX;i++){
		ull prefix_sum = 0;
		for(ull gm = i; gm <MAX; gm+=i ){
			lsum[i]+= mulmod(prefix_sum * cnt[gm] , gm);
			lsum[i]+= mulmod((gm * gm % MOD ) ,  mulmod(mulmod(cnt[gm]  , (cnt[gm] -1)) , dp[2]));
			lsum[i]%=MOD;
			prefix_sum +=(cnt[gm] * gm % MOD);
			prefix_sum%=MOD;
		}
	}
	for(int i=MAX-1;i>0;i--){
		for(int gm = i*2; gm < MAX; gm +=i){
			lsum[i] -= lsum[gm];
			if(lsum[i] < 0) lsum[i]+=MOD;
		}
		if(lsum[i]!=0){
		maxSum += mulmod(lsum[i] , dp[i]);
		maxSum%=MOD;}
	}
	if(maxSum < 0) maxSum+=MOD;
	cout << maxSum <<endl;
	return 0;
}
