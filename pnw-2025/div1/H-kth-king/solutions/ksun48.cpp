#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N;
	cin >> N;
	vector<ll> A(N);
	for(int i = 0; i < N; i++){
		cin >> A[i];
	}
	sort(A.begin(), A.end());
	vector<ll> pA(N+1);
	for(int i = 0; i < N; i++){
		pA[i+1] = pA[i] + A[i];
	}
	for(int i = N; i >= 1; i--){
		ll ans = pA[i] - pA[(i+1)/2] - pA[i/2] + pA[0];
		cout << ans << '\n';
	}
}
