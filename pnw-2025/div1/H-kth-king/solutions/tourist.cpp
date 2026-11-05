/**
 *    author:  tourist
 *    created: 26.10.2025 19:42:22
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
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  vector<int64_t> res(n);
  int64_t ans = 0;
  for (int i = 0; i < n; i++) {
    ans += a[i] - a[i / 2];
    res[i] = ans;
  }
  for (int i = n - 1; i >= 0; i--) {
    cout << res[i] << '\n';
  }
  return 0;
}
