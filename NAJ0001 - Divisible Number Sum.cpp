#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
vector<int>p[1001];
void factor(int n ,int indx)
{
	if(n%2==0){
	for(int i=1;i<=sqrt(n);i++)
	{
		if(n%i==0)
		{
			p[i].push_back(indx);
			if(n/i!=i){if(n/i < 1001)p[n/i].push_back(indx);}
		}
	}}
	else
	{
	for(int i=1;i<=sqrt(n);i+=2)
	{
		if(n%i==0)
		{
			p[i].push_back(indx);
			if(n/i!=i){if(n/i < 1001)p[n/i].push_back(indx);}
			}
		}
	}
}
inline uint scan()
    {
        uint z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void put_uint64(ull n) {
  char stack[20];
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
int main() {
	int tc;
	cin >> tc;
	for(int cs=1;cs<=tc;cs++)
	{
		int n,m;
		printf("Case #%d\n",cs);
		uint arr[100011]={0},num;
		vector<ull>csum[1001];
		vector<int>::iterator lo,hi;
		n=scan();m=scan();
		for(int i=0;i<n;i++)
		{
			arr[i]=scan();
		}
		for(int i=0;i<1001;i++)
		{
			p[i].clear();
			csum[i].clear();
		}
		for(int i=0;i<n;i++)
		{
			factor(arr[i],i);
		}
		for(int i=1;i<=1000;i++)
		{
			csum[i].push_back(0);
		}
		for(int i=1;i<=1000;i++)
		{
			ull sum = 0;
			for(int j=0;j<p[i].size();j++)
			{
				sum+=arr[p[i][j]];
				csum[i].push_back(sum);
			}
		}
		uint x,y,v,x1,y1;
		for(uint q=1;q<=m;q++)
		{
			
			v=scan();x=scan();y=scan();
			lo = lower_bound(p[v].begin(),p[v].end(),x-1);
			y1 = lower_bound(lo,p[v].end(),y)-p[v].begin();
			put_uint64(csum[v][y1]-csum[v][lo-p[v].begin()]);
		}
		cout<<endl;
	}
	return 0;
}


