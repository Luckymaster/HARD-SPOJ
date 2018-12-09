#include<iostream>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
#define N 160180000
#define MAXN 160180000
unsigned phi[MAXN + 1], prime[MAXN/10], sz=0;
vector<bool>mark(MAXN,0);
int b[MAXN];
inline unsigned scan()
    {
        unsigned z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
int main()
{
   phi[1] = 1;b[1]=-1; 
     for (int i = 2; i <= MAXN; i++ ){b[i]=-1;
    	if(!mark[i]){
    		phi[i] = i-1;
    		prime[sz++]= i;
    	}
    	for (int j=0; j<sz && prime[j]*i <= MAXN; j++ ){
    		mark[prime[j]*i]=1;
    		if(i%prime[j]==0){
    			phi[i*prime[j]] = phi[i]*prime[j];break;
    		}
    		else phi[i*prime[j]] = phi[i]*(prime[j]-1 );
    	}
    }
for(int i=1 ;i<MAXN;i++)
{ 
  int x=0;
   if(b[phi[i]] > 0)
    {
       x = min(b[phi[i]],i);
      b[phi[i]]=x;
    }
  else
  {
    b[phi[i]]=i;
 }
 }
   int tc;
   tc=scan();
   while(tc--)
   {
    int n;
    n=scan();
    printf("%d\n",b[n]);             
   } 
   return 0;    
}