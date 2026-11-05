#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N, D, M;
	cin >> N >> D >> M;
	vector<int> S(N);
	for(int i = 0; i < N; i++) cin >> S[i];
	sort(S.begin(), S.end());

	int cur = D;
	ll tot = -ll(D) * ll(M);
	for(int i = 0; i < N; i++){
		tot += cur;
		if(tot >= 0){
			cout << (i+1) << '\n';
			exit(0);
		}
		cur -= S[i];
	}
	cout << -1 << '\n';
}
