#include <bits/stdc++.h>
using namespace std;
#define ul unsigned long long
#include <boost/lexical_cast.hpp>
unordered_map<string,int> l;
vector<ul> ss;string s1;
int main(){
	int x,y,M=1000001;
	cin>>x>>y;y>84313?M:M/=10;
	for(ul i=11;i<M;i++){
		s1=boost::lexical_cast<std::string>(i*i);
		sort(s1.begin(),s1.end());l[s1]++;
	}
	for(ul i=11;i<M;i++){
		s1=boost::lexical_cast<std::string>(i*i);
		sort(s1.begin(),s1.end());
		if(l[s1]>1){
			ss.push_back(i*i);
		}
	}
	for(ul i=x-1;i<y;i++){
		printf("%lld\n",ss[i]);
	}
	return 0;
}
