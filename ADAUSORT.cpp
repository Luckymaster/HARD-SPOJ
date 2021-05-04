#include <bits/stdc++.h>
using namespace std;
struct sort_pred {
    bool operator()(const std::pair<uint,uint> &left, const std::pair<uint,uint> &right) {
        return (left.first < right.first)? 1 :((left.first == right.first) && (left.second > right.second))? 1:0;
    }
};

int main() {
	uint n,k;
	vector<pair<uint,uint> >vect;
	ios_base::sync_with_stdio(false);cin.tie(0); 
	cin >> n;
	for(uint i=1;i<=n;i++){
		cin >> k;
		vect.push_back(make_pair(k,i));
	}
	sort(vect.begin(),vect.end(),sort_pred());
	for(uint i=0;i<vect.size();i++){
		cout<<vect[i].second<<" ";
	}
	return 0;
}
