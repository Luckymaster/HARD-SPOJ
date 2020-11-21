#include<iostream>
#define mod1 1000000007
#define mod2 1000000006
#define mod3 500000003
#include<cstdio>
#include<cmath>
#define lli long long 
lli MT=250000002;
using namespace std;
lli combination(int n);
lli mul(lli a,lli b,lli c);
lli CRT();
lli modpow(lli a,lli b,lli c);
int mod[] = {2,41 * 41,148721};//prime factor of 500000002
int rem[3];
lli fact1[200005],inv,fact2[148721];
inline int scan()
    {
        int z=0;
        char c;
        do{ c=getchar_unlocked(); } while(c<'0');
        for(;c>='0';c=getchar_unlocked()) z = (z<<3) + (z<<1) + (c&15);
        return z;
    }
inline void fastWrite(int a)
{
    char snum[20];
    int i=0;
    do
    {
        snum[i++]=a%10+48;
        a=a/10;
    }
    while (a);
    i=i-1;
    while (i>=0)
        putchar(snum[i--]);
    putchar('\n');
}
lli eculid(lli a,lli b, lli &x, lli &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    
    long long g = eculid(b,a % b,y,x);
    y -= a / b * x;
    return g;
}
lli modinv(lli a, lli m){
    lli x,y;
    eculid(a, m, x, y);
    return (x % m + m) % m;
}

lli mul(lli a,lli b,lli c){
    lli x = 0,y=a%c;
    while(b > 0){
        if(b & 1){
            x = (x+y)%c;
        }
        y = (y<<1)%c;
        b>>=1;
    }
    return x%c;
}
lli modpow(lli a,lli b,lli c){
    lli x=1,y=a; 
    while(b > 0){
        if(b & 1){
            x=(x*y)%c;
        }
        y = (y*y)%c; 
        b>>=1;
    }
    return x%c;
}
lli CRT(){
    lli ans = rem[0],m = mod[0];
  
    for(int i = 1;i < 3;++i){
        int a = modinv(m,mod[i]);
        int b = modinv(mod[i],m);
        
        ans = (ans * b * mod[i] + (long long)rem[i] * a * m) % (m * mod[i]);
        m *= mod[i];
    }
    
    return ans;
}

lli combination(int n){
    rem[0] = 0;
    int val1 = 0;
    int temp = 2 * n;
    while(temp){
        val1 += temp / 41; temp /= 41;
    }int val2 = 0;
    temp = n;
while(temp){
        val2 += temp / 41; temp /= 41;
    }
   val1 -= 2 * val2;
    if(val1 >= 2) rem[1] = 0;
    else{
        rem[1] = fact1[2 * n] * modinv(fact1[n] * fact1[n] % mod[1],mod[1]) % mod[1];
        if(val1 == 1) rem[1] = rem[1] * 41 % mod[1];
    }
    if(2 * n >= mod[2]) rem[2] = 0;
    else rem[2] = fact2[2 * n] * modpow(fact2[n] * fact2[n] % mod[2],mod[2] - 2,mod[2]) % mod[2];
    
    return CRT();
}
void calcfact()
{
    fact1[0] = 1;
    for(int i = 1;i <= 200000;++i){
        int temp1 = i;
        while(temp1 % 41 == 0) temp1 /= 41;
        fact1[i] = fact1[i - 1] * temp1 % 1681;
    }
    fact2[0] = 1;
    for(int i = 1;i < 148721;++i)
        fact2[i] = fact2[i - 1] * i % 148721;
}

int main(){
    calcfact();
    lli finalans,two;
    lli res=0;
    int tc,a,b,n;
    tc=scan();
    while(tc--){
        a=scan();
        b=scan();
        n=scan();
        lli temp3 ;
        int finalans = 0;
        int invq = 1;
        if(b != 0){
            int temp4 = (b % 2 == 0? 0 : 1);
            lli remq = modpow(b,combination(n),mod3);
            finalans = (temp4 * mod3 * invq + remq * 2 * MT) % mod2;
        }
        finalans = modpow(a,finalans,mod1);
        fastWrite(finalans);
    }
return 0;
}
