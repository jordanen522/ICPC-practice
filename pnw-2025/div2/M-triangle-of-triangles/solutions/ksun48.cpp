#include <bits/stdc++.h>
using namespace std;

void solve(){
	vector<int> T1(3), T2(3), T3(3);
	for(int i = 0; i < 3; i++) cin >> T1[i];
	for(int i = 0; i < 3; i++) cin >> T2[i];
	for(int i = 0; i < 3; i++) cin >> T3[i];
	for(int i = 0; i < 3; i++){
		for(int c = 5; c < T1[i]; c += 5){
			vector<int> r1 = {c, T1[(i+1)%3], 180 - c - T1[(i+1)%3]};
			vector<int> r2 = {T1[i]-c, T1[(i+2)%3], 180 - (T1[i]-c) - T1[(i+2)%3]};
			sort(r1.begin(), r1.end());
			sort(r2.begin(), r2.end());
			if(r1 == T2 || r1 == T3){
				if(r2 == T2 || r2 == T3){
					cout << "YES" << '\n';
					return;
				}
			}
		}
	}
	cout << "NO" << '\n';
	return;
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--) solve();
}
