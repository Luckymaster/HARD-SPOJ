#include <bits/stdc++.h>
using namespace std;
#define MAXK 325
typedef long long LL;
#define MOD 1234567891

LL coeff[MAXK+1][MAXK+1];
LL b[MAXK+1][MAXK+1];
int x[MAXK+1];
int inv[MAXK+1];

LL mulmod(LL a, LL b, LL mod) {
    LL res = (a * ((long double) b / (long double) mod));
    res = a * b - res * mod;
    if (res >= mod) res -= mod;
    if (res < 0) res += mod;
    return res;
}
void init()
{
    coeff[0][0]=1;
    for(int i=1;i<=MAXK;i++)
	{
		for(int j = 0; j<=i;j++)coeff[i][j]=0;
		for(int j = 0;j<=i-1;j++){
			coeff[i][j+1] = coeff[i][j+1]+coeff[i-1][j]%MOD;
			coeff[i][j] = (coeff[i][j]+mulmod(coeff[i-1][j],(i-1),MOD))%MOD;
		}
	}
}
void init1()
{
    for(int i=0;i<=MAXK;i++){
      for(int j=0;j<i;j++) x[j] = 0;
      x[i] = 1;
      for(int j=i;j>=0;j--){
        LL q = x[j];
        b[i][j] = q;
        for(int k=j;k>=0;k--){
          x[k] = (x[k]-mulmod(q,coeff[j][k],MOD))%MOD;
        }
      }
    }
}
int modInverse(int a, int n) 
{
        int i = n, v = 0, d = 1;
        while (a > 0) 
        {
                int t = i/a, x = a;
                a = i % x;
                i = x;
                x = d;
                d = v - t*x;
                v = x;
        }
        v %= n;
        if (v < 0) v = (v+n)%n;
 return v;
}
void init2()
{   
    for(int i=1;i<MAXK;i++)
    {
       inv[i] = modInverse(i,MOD);
      }
}
LL solve(LL n, int k)
  {
    LL ans = 0,ans1=0;
    int i;
    LL seed = 1,seed1=0;
    for( i=0;i<=k;i++)
    {
      seed = mulmod(seed , (n+i) , MOD);
      seed1 = seed;
      ans = (ans + (seed * mulmod(b[k][i] , inv[i+1] , MOD) % MOD));
      ans1 = (ans1 + (seed * mulmod(b[k+1][i],inv[i+1] ,MOD) % MOD));
      ans1%=MOD;
      ans%=MOD;
    }
    seed1 = mulmod(seed1 , (n+i) , MOD);
    ans1 = (ans1 +(seed1 * mulmod(b[k+2][i+1],inv[i+1] ,MOD) %MOD));
    ans1%=MOD;
    return (ans*(n+1)-ans1+MOD)%MOD;
  }

inline int scan()
    {
        int z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void put_uint(int n) {
  char stack[12];
  int top = 0;
  if(n == 0) {
    putchar_unlocked('0');
  } else {
    while(n > 0) {
      stack[top++] = n % 10 + '0';
      n /= 10;
    }
    while(top > 0) {
      putchar_unlocked(stack[--top]);
    }
  }
  putchar_unlocked('\n');
}
int main()
{
        int n;
        int tc,k;init2();
        init();init1();
        scanf("%d",&tc);
        for(int cs=1;cs<=tc;cs++)
        {   
                n=scan();k=scan();
                LL sum = solve(n,k);
                put_uint(sum);
        }
}

