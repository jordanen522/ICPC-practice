/**
 *    author:  tourist
 *    created: 28.10.2025 12:04:43
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
  int n, d, m;
  cin >> n >> d >> m;
  vector<int> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  sort(s.begin(), s.end());
  int r = 0;
  int64_t sum = 0;
  for (int i = 0; i < n; i++) {
    if (r >= d) {
      break;
    }
    sum += d - r;
    if (sum >= int64_t(d) * m) {
      cout << i + 1 << '\n';
      return 0;
    }
    r += s[i];
  }
  cout << -1 << '\n';
  return 0;
}
