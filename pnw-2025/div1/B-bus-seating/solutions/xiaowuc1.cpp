#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n, k, m, c;
  cin >> n >> k >> m >> c;
  vector<int> rows(m);
  for(auto& x: rows) cin >> x;
  vector<int> used(n+1);
  vector<set<int>> dp(k);
  for(int i = 1; i <= n; i++) dp[0].insert(i);
  vector<int> ret(m);
  int lhs = 0;
  for(int i = 0; i < m; i++) {
    array<int64_t, 3> best = {0, 1, -1}; // <num, denom, idx>
    auto upd = [&](int64_t num, int64_t denom, int idx) -> void {
      if(num*best[1] > denom*best[0] || (num*best[1] == denom*best[0] && idx < best[2])) {
        best = {num, denom, idx};
      }
    };
    while(dp[lhs].size() == 0) lhs++;
    for(int x = lhs; x <= lhs + 30 && x < k; x++) {
      auto it = dp[x].lower_bound(rows[i]);
      if(it != dp[x].end()) {
        int crow = *it;
        upd(c - abs(crow - rows[i]), 1 << (x - lhs), crow);
      }
      if(it != dp[x].begin()) {
        it--;
        int crow = *it;
        upd(c - abs(crow - rows[i]), 1 << (x - lhs), crow);
      }
    }
    int cand = best[2];
    ret[i] = cand;
    dp[used[cand]].erase(cand);
    if(++used[cand] < k) dp[used[cand]].insert(cand);
  }
  for(int i = 0; i < m; i++) cout << ret[i] << " \n"[i == m-1];
}
