/**
 *    author:  tourist
 *    created: 26.10.2025 18:42:20
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
  int tt;
  cin >> tt;
  while (tt--) {
    array<int, 3> a, b, c;
    for (int i = 0; i < 3; i++) {
      cin >> a[i];
    }
    for (int i = 0; i < 3; i++) {
      cin >> b[i];
    }
    for (int i = 0; i < 3; i++) {
      cin >> c[i];
    }
    bool win = false;
    for (auto d : {b, c}) {
      for (auto e : {b, c}) {
        do {
          do {
            if (d[0] + e[0] == 180) {
              array<int, 3> f = {d[1] + e[1], d[2], e[2]};
              sort(f.begin(), f.end());
              win |= (f == a);
            }
          } while (next_permutation(e.begin(), e.end()));
        } while (next_permutation(d.begin(), d.end()));
      }
    }
    cout << (win ? "YES" : "NO") << '\n';
  }
  return 0;
}
