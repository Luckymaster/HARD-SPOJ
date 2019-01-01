#include <bits/stdc++.h>
using namespace std;
inline void s(int limit, int s_size=39000)
{ unsigned long long  sum=2;
  int sq=sqrt(limit),count=(limit<2)?0:1,s=2,n=3,p=2,j,k,i;
  vector<char>seg(s_size);
  vector<char>is_prime(sq+1,1);
  for(i=2;i*i<=sq;i++)
    if (is_prime[i])
      for (j=i*i;j<=sq;j+=i)is_prime[j]=0;
  vector<int> primes,next;
  for (int low=0;low<=limit; low+=s_size)
  {fill(seg.begin(), seg.end(), 1);
    int hi = min(low+s_size-1,limit);
    for (; s * s <= hi; s++)
      if (is_prime[s])
      {primes.push_back((int) s);next.push_back((int)(s * s - low));
      } for (size_t i=1; i < primes.size(); i++)
    { j = next[i];for (k = (primes[i]<<1); j<s_size; j += k)
        seg[j] = 0;next[i]=j-s_size;}
    for (;n<=hi;n+=2)if (seg[n-low]) sum+=n;}cout<<sum<<endl;}
int main(){int l;cin>>l;s(l);}
