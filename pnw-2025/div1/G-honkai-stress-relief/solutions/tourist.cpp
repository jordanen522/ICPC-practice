/**
 *    author:  tourist
 *    created: 26.10.2025 19:47:39
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
  int n, a, b;
  cin >> n >> a >> b;
  __int128 num = 1;
  for (int i = 0; i < n; i++) {
    int s, e;
    cin >> s >> e;
    s = max(s, a);
    e = min(e, b);
    num *= max(0, e - s);
  }
  cout << fixed << setprecision(6) << 1 - num / pow(b - a, n) << '\n';
  return 0;
}
