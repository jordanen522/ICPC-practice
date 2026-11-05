/**
 *    author:  tourist
 *    created: 26.10.2025 18:50:22
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
  int ma = *max_element(a.begin(), a.end());
  int mb = *max_element(b.begin(), b.end());
  int ans = numeric_limits<int>::max();
  for (int sa = ma - n; sa <= ma; sa++) {
    for (int sb = mb - n; sb <= mb; sb++) {
      vector f(n + 1, vector<bool>(n + 1));
      f[0][0] = true;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
          if (f[i][j]) {
            int xa = sa + j;
            int xb = sb + (i - j);
            if (xa >= a[i] && xb >= b[i]) {
              f[i + 1][j] = true;
              f[i + 1][j + 1] = true;
            }
          }
        }
      }
      if (f[n] != vector<bool>(n + 1, false)) {
        ans = min(ans, sa + sb);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
