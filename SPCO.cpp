#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
typedef unsigned long long i64;
using namespace std;
vector<int> p;
int primes[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61};
    inline i64 scan()
    {
       i64 z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
struct Chooser{
    i64 val[64][64];
 
    Chooser(){
        for (int i=0; i<64; i++)
            for (int j=0; j<64; j++)
                val[i][j]=(i==j or j==0? 1: i<j? 0: val[i-1][j]+val[i-1][j-1]);
    }
 
   i64 operator()(int n,int r) const{
        return n>=0 and r>=0? val[n][r]: 0llu;
    }
} const choose;

struct SuffixSolver{
    i64 answer[64][64];
    
    SuffixSolver(){
    	for(int i=0;i<18;i++)p.push_back(primes[i]);
        for (int i=0; i<64; i++)
            for (int j=0; j<64; j++)
                for (int k=answer[i][j]=0; k<p.size(); k++)
                    answer[i][j]+=choose(i,p[k]-j);
    }
 
    i64 get(int suffixbits,int prefixones) const{
        return answer[suffixbits][prefixones];
    }
} const solver;
 
i64 primebits(i64 n){
    i64 res=0llu;
    int pop=__builtin_popcountll(n);
    for (int suffix=0; n; n>>=1ll, ++suffix)
        if (n&1llu)
            res+=solver.get(suffix,--pop);
    return res;
}
inline void fastWrite(i64 a)
{
    char snum[21];
    int i=0;
    do
    {
        snum[i++]=a%10+48;
        a=a/10;
    }
    while (a);
    i=i-1;
    while (i>=0)
        putchar_unlocked(snum[i--]);
    putchar_unlocked('\n');
}
int main() {
	unsigned tc;
	i64 a,b;
	
	scanf("%u",&tc);
	for(unsigned i=1;i<=tc;i++)
	{  
		a=scan();b=scan();
		fastWrite((primebits(b+1)-primebits(a)));
	}
	return 0;
}
