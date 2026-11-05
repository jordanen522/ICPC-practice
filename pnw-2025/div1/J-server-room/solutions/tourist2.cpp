/**
 *    author:  tourist
 *    created: 26.10.2025 19:29:44
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

struct State {
  int cnt = int(-1e9);
  int64_t ways = 0;

  State operator +(const State& other) const {
    State ret;
    ret.cnt = max(cnt, other.cnt);
    ret.ways = ((cnt == ret.cnt ? ways : 0) + (other.cnt == ret.cnt ? other.ways : 0)) % 998244353;
    return ret;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int r, c;
  cin >> r >> c;
  vector<string> s(r);
  for (int i = 0; i < r; i++) {
    cin >> s[i];
  }
  if (r < c) {
    swap(r, c);
    vector<string> ns(r, string(c, ' '));
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        ns[i][j] = s[j][i];
      }
    }
    s = ns;
  }
  vector<State> f(1 << c);
  f[0] = {0, 1};
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      vector<State> nf(1 << c);
      for (int t = 0; t < (1 << c); t++) {
        if (f[t].cnt < 0) {
          continue;
        }
        for (int w = 0; w <= 1; w++) {
          if (w == 0 && s[i][j] == '2') {
            continue;
          }
          if (w == 1) {
            if (s[i][j] == '0') {
              continue;
            }
            if (((t >> j) & 1)) {
              continue;
            }
            if (j > 0 && ((t >> (j - 1)) & 1)) {
              continue;
            }
          }
          int nt = (t & ~(1 << j)) | (w << j);
          auto ft = f[t];
          ft.cnt += w;
          nf[nt] = nf[nt] + ft;
        }
      }
      swap(f, nf);
    }
  }
  State ans;
  for (int t = 0; t < (1 << c); t++) {
    ans = ans + f[t];
  }
  int sub = 0;
  for (int i = 0; i < r; i++) {
    sub += int(count(s[i].begin(), s[i].end(), '2'));
  }
  cout << ans.cnt - sub << " " << ans.ways << '\n';
  return 0;
}
