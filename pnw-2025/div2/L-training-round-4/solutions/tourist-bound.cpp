/**
 *    author:  tourist
 *    created: 26.10.2025 19:00:07
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
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }
  int ans = -1;
  for (int pa = 0; pa < n; pa++) {
    for (int pb = 0; pb < n; pb++) {
      ans = max(ans, a[pa] + b[pb] - max(pa, pb));
    }
  }
  cout << ans << '\n';
  return 0;
}
