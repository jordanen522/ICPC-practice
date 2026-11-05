#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N;
	cin >> N;
	vector<vector<int>> probs(N, vector<int>(2));
	for(int i = 0; i < N; i++){
		cin >> probs[i][0] >> probs[i][1];
	}
	vector<int> maxprob(2, 0);
	for(int i = 0; i < N; i++){
		for(int c = 0; c < 2; c++){
			maxprob[c] = max(maxprob[c], probs[i][c]);
		}
	}
	vector<vector<int> > dp = {{1}};
	for(int n = N-1; n >= 0; n--){
		vector<vector<int> > ndp(N-n+1, vector<int>(N-n+1, 0));
		for(int a = 0; a <= N-n; a++){
			for(int b = 0; b <= N-n; b++){
				int sa = maxprob[0] - a;
				int sb = maxprob[1] - b;
				if(sa >= probs[n][0] && sb >= probs[n][1]){
					if(b < N-n && dp[max(a-1, 0)][b]) ndp[a][b] = 1;
					if(a < N-n && dp[a][max(b-1, 0)]) ndp[a][b] = 1;
				}
			}
		}
		dp = ndp;
	}
	int ans = maxprob[0] + maxprob[1];
	for(int i = 0; i <= N; i++){
		for(int j = 0; j <= N; j++){
			if(dp[i][j]){
				ans = min(ans, maxprob[0] + maxprob[1] - i - j);
			}
		}
	}
	cout << ans << '\n';
}
