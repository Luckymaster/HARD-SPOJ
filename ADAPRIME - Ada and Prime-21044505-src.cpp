#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <ctime>
#include <cmath>
#include <cfloat>
#include <cstring>
#include <climits>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/spirit/include/karma.hpp>
using namespace std;
typedef unsigned ui;
typedef unsigned long long ull;
//Prime number algorithm by Mike ;)
ui const N_ = 800000, N = N_ % 64 ? N_ + 64 - N_ % 64 : N_, N2 = N / 2, N64 = N / 64, C = 1000, M = 999999999, SM=100500;
ui be[SM>>1], sn=3;
ui a[N64], b[N64+(SM>>5)];

ui const NP = 50847639, A = 64;
ui mod;
double imod;
char *num;
ui pr[10], npr=2;
boost::unordered_map<string,ui> primeper;
vector<string>mytst;
using namespace std;
//Note: Define USE_SPIRIT to include Karma (requires Boost 1.45+)
#define USE_SPIRIT
#ifdef USE_SPIRIT
 #define INCLUDE_KARMA
 #include <boost/spirit/include/karma.hpp>
#endif
namespace hopman_fast
{
   struct itostr_helper
   {
      static unsigned out[10000];

      itostr_helper()
      {
         for (int i = 0; i < 10000; i++)
         {
            unsigned v = i;
            char * o = (char*)(out + i);
            o[3] = v % 10 + '0';
            o[2] = (v % 100) / 10 + '0';
            o[1] = static_cast<char>((v % 1000) / 100) + '0';
            o[0] = static_cast<char>((v % 10000) / 1000);
            if (o[0]) o[0] |= 0x30;
            else if (o[1] != '0') o[0] |= 0x20;
            else if (o[2] != '0') o[0] |= 0x10;
            else o[0] |= 0x00;
         }
      }
   };

   unsigned itostr_helper::out[10000];

   itostr_helper hlp_init;

   template <typename T>
   std::string itostr(T o)
   {
      typedef itostr_helper hlp;

      unsigned blocks[3], *b = blocks + 2;
      blocks[0] = o < 0 ? ~o + 1 : o;
      blocks[2] = blocks[0] % 10000; blocks[0] /= 10000;
      blocks[2] = hlp::out[blocks[2]];

      if (blocks[0])
      {
         blocks[1]  = blocks[0] % 10000; blocks[0] /= 10000;
         blocks[1]  = hlp::out[blocks[1]];
         blocks[2] |= 0x30303030;
         b--;
      }

      if (blocks[0])
      {
         blocks[0]  = hlp::out[blocks[0] % 10000];
         blocks[1] |= 0x30303030;
         b--;
      }

      char* f = ((char*)b);
      f += 3 - (*f >> 4);

      char* str = (char*)blocks;
      if (o < 0) *--f = '-';
      return std::string(f, (str + 12) - f);
   }
}
inline bool karma_int_to_string(const int& value, std::string& str)
{
  using namespace boost::spirit;
  using boost::spirit::karma::generate;
  char buffer[16];
  char* x = buffer;
  if (!generate(x, int_, value))
     return false;
  str.assign(buffer, x - buffer);
  return true;
}

inline void add(ui p) {
	string ss=hopman_fast::itostr(p);
	//karma_int_to_string(p,ss);//boost::lexical_cast<std::string>(p);
	boost::sort(ss);
	primeper[ss]++;
}
inline void resheto() {
	memset(be,0xff, sizeof be);
	a[0] = 1;
	for (ui j, i=3; i*i<N; i+=2)
		if (!(a[i>>6]>>(i>>1&31)&1))
			for (j=(i*i>>1); j<N2; j+=i)
				a[j>>5] |= 1<<(j&31);
	for (ui i=0; i<N64; i++)
		for (ui x = a[i], j = __builtin_ffs(~x)-1; j < 32; x |= 1<<j, j = __builtin_ffs(~x)-1)
			add(2*(i<<5|j)+1);
}
inline ui fst(ui n, ui p) {
	ui k = p - n%p;
	if (!(k&1)) k+=p;
	return k>>1;
}
inline ui fst3(ui n, ui p) {
	ui k = p - n%p;
	if (!(k&1)) k+=p;
	if (!((n+k) % 3)) k+=p<<1;
	if (!((n+k+(p<<1)) % 3)) k+=p<<2;
	return k>>1;
}
ui r[C];
inline void resheto(ui n) {
	ui msk[4];
	memset(msk, 0, sizeof msk);
	for (ui x=3, y=x; ; x=y) {
		ui c = 1;
		for (; c*y<=C; y+=2)
			if (!(a[y>>6]>>(y>>1&31)&1))
				c*=y;
		if (c<x*x)
			break;
		memset(r, 0, c*sizeof(*r));
		for (ui i=x; i<y; i+=2)
			if (!(a[i>>6]>>(i>>1&31)&1)) {
				msk[i>>6] |= 1<<(i>>1&31);
				for (ui j=fst(n,i); (j>>5)<c; j+=i)
					r[j>>5] |= 1<<(j&31);
			}
		ui i=0;
		if (x==3) {
			for (; i<N64-c; i+=c)
				for (ui j=0; j<c; j++)
					b[i+j] = r[j];
			for (ui j=0; j<N64-i; j++)
				b[i+j] = r[j];
		} else {
			for (; i<N64-c; i+=c)
				for (ui j=0; j<c; j++)
					b[i+j] |= r[j];
			for (ui j=0; j<N64-i; j++)
				b[i+j] |= r[j];
		}
	}
	
	for (; sn*sn<n+N; sn+=2);

	for (ui i=0; i<4; i++)
		a[i]^=msk[i];

    #pragma omp parallel for schedule(guided)
	for (ui i=0; i<<6 < sn; i++)
		for(ui c, j, d = a[i], e=__builtin_ffs(~d)-1; e<32; d |= 1<<e, e=__builtin_ffs(~d)-1) {
			c=((i<<5|e)<<1|1), j=(be[c>>1]<N2 ? be[c>>1] : fst3(n,c));
			if (j>=c<<1)
				b[(j-(c<<1))>>5] |= 1<<((j-(c<<1))&31);
			for (; j<N2; j+=c+(c<<1))
				b[j>>5] |= 1<<(j&31), b[(j+c)>>5] |= 1<<((j+c)&31);
			be[c>>1] = j - N2;
		}

	for (ui i=0; i<4; i++)
		a[i]^=msk[i];

   #pragma omp parallel for schedule(guided)
	for (ui i=0; i<N64; i++)
		for (ui x = b[i], j = __builtin_ffs(~x)-1; j < 32; x |= 1<<j, j = __builtin_ffs(~x)-1)
			add(n + 2*(i<<5|j)+1);
}
void compute(){
	pr[0]=2;pr[1]=3;
	resheto();
	string ss ="";
	for (ui i=1; i*N<M; i++)
		resheto(i*N);
	for(int i=0;i<npr;i++){
		ss = boost::lexical_cast<std::string>(pr[i]);
		sort(ss.begin(),ss.end());
		primeper[ss]++;
	}
}
int main(){
	pr[0]=2;pr[1]=3;
	primeper["2"]=1;
	resheto();
	for (ui i=1; i*N<M; i++)
		resheto(i*N);
	int T,N;
	ios_base::sync_with_stdio(false);
	cin >> T;
	while(T--){
		cin >> N;
		string ss="",s;
		int num[N+1];
		for(int i=0;i<N;i++){
			cin >> s;
			ss+=s;
		}
		boost::sort(ss);
		cout<<primeper[ss]<<endl;
	}
}