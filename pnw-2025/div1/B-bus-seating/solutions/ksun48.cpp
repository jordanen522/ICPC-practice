#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N, K, M, C;
	cin >> N >> K >> M >> C;
	int B = 0;
	while((1 << B) <= N) B++;
	vector<set<int> > rows_by_cnt(K+1);
	vector<int> taken(N, 0);
	for(int i = 0; i < N; i++){
		rows_by_cnt[taken[i]].insert(i);
	}
	int a = 0;
	for(int i = 0; i < M; i++){
		while(rows_by_cnt[a].empty()) a++;

		int r;
		cin >> r; r--;

		pair<ll, int> best_score = {0, 0};
		for(int c = a; c < a + B && c < K; c++){
			auto it = rows_by_cnt[c].lower_bound(r);
			int loc = -1;
			if(it != rows_by_cnt[c].end()){
				loc = *it;
			}
			if(it != rows_by_cnt[c].begin()){
				int nloc = *prev(it);
				if(loc == -1 || pair<int,int>{abs(nloc - r), nloc} < pair<int,int>{abs(loc - r), loc}){
					loc = nloc;
				}
			}
			if(loc >= 0){
				pair<ll, int> score = {-ll(C - abs(loc - r)) * ll(1 << (a + B - c)), loc};
				if(score < best_score){
					best_score = score;
				}
			}
		}
		int sit = best_score.second;
		assert(sit != -1);
		cout << (sit+1) << " \n"[i+1 == M];
		rows_by_cnt[taken[sit]].erase(sit);
		taken[sit]++;
		rows_by_cnt[taken[sit]].insert(sit);
	}
}
