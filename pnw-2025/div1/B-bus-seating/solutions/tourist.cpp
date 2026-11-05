/**
 *    author:  tourist
 *    created: 28.10.2025 12:15:51
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k, m, c;
  cin >> n >> k >> m >> c;
  vector<set<int>> s(k + 1);
  for (int i = 0; i < n; i++) {
    s[0].insert(i);
  }
  set<int> counts = {0};
  for (int i = 0; i < m; i++) {
    int a;
    cin >> a;
    --a;
    array<int, 3> best = {-1, -1, -1};
    int last_p = -1;
    for (int p : counts) {
      if (last_p >= 0) {
        for (int j = 0; j < p - last_p; j++) {
          best[0] *= 2;
          if (best[0] > c) {
            break;
          }
        }
        if (best[0] > c) {
          break;
        }
      }
      last_p = p;
      auto it = s[p].lower_bound(a);
      if (it != s[p].end()) {
        array<int, 3> cur = {c - abs((*it) - a), -(*it), p};
        best = max(best, cur);
      }
      if (it != s[p].begin()) {
        --it;
        array<int, 3> cur = {c - abs((*it) - a), -(*it), p};
        best = max(best, cur);
      }
    }
    int row = -best[1];
    s[best[2]].erase(row);
    s[best[2] + 1].insert(row);
    if (s[best[2]].empty()) {
      counts.erase(best[2]);
    }
    if (best[2] + 1 < k) {
      counts.insert(best[2] + 1);
    }
    cout << row + 1 << " \n"[i == m - 1];
  }
  return 0;
}
