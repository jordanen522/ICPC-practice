#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N, Q;
	cin >> N >> Q;

	int M = 51;
	vector<int> toys(N, 0);
	vector<int> all_toy_counts(M);
	vector<vector<int> > adj(N);
	vector<vector<int> > neighbor_toy_counts(N, vector<int>(M, 0));
	for(int v = 0; v < N; v++){
		all_toy_counts[toys[v]]++;
		adj[v].push_back(v);
		neighbor_toy_counts[v][toys[v]]++;
	}
	for(int q = 0; q < Q; q++){
		char c;
		cin >> c;
		if(c == 'F'){
			int u, v;
			cin >> u >> v;
			u--; v--;
			neighbor_toy_counts[u][toys[v]]++;
			neighbor_toy_counts[v][toys[u]]++;
			adj[u].push_back(v);
			adj[v].push_back(u);
		} else if(c == 'A'){
			int u;
			cin >> u;
			u--;
			for(int v : adj[u]){
				neighbor_toy_counts[v][toys[u]]--;
			}
			all_toy_counts[toys[u]]--;
			toys[u]++;
			all_toy_counts[toys[u]]++;
			for(int v : adj[u]){
				neighbor_toy_counts[v][toys[u]]++;
			}
		} else if(c == 'Q'){
			int v;
			cin >> v;
			v--;
			int ans = -1;
			for(int k = M-1; k >= 0; k--){
				if(all_toy_counts[k] > neighbor_toy_counts[v][k]){
					ans = k;
					break;
				}
			}
			cout << ans << '\n';
		}
	}
}
