/**
 *    author:  tourist
 *    created: 26.10.2025 19:56:29
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
  int n, q;
  cin >> n >> q;
  const int M = 51;
  vector<int> cnt(n + 1);
  vector<vector<int>> g(n + 1);
  vector nei(n + 1, vector<int>(M));
  auto Add = [&](int i, int j) {
    g[i].push_back(j);
    nei[i][cnt[j]] += 1;
  };
  for (int i = 0; i <= n; i++) {
    Add(i, i);
  }
  for (int i = 0; i < n; i++) {
    Add(i, n);
    Add(n, i);
  }
  while (q--) {
    string op;
    cin >> op;
    if (op == "F") {
      int i, j;
      cin >> i >> j;
      --i; --j;
      Add(i, j);
      Add(j, i);
    }
    if (op == "A") {
      int i;
      cin >> i;
      --i;
      for (int j : g[i]) {
        nei[j][cnt[i]] -= 1;
        nei[j][cnt[i] + 1] += 1;
      }
      cnt[i] += 1;
    }
    if (op == "Q") {
      int i;
      cin >> i;
      --i;
      int ans = -1;
      for (int x = 0; x < M; x++) {
        if (nei[n][x] != nei[i][x]) {
          ans = x;
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
