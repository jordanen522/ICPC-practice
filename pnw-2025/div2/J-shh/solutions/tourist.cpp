/**
 *    author:  tourist
 *    created: 26.10.2025 19:14:49
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

struct State {
  int cnt = int(1e9);
  int64_t ways = 0;

  State operator +(const State& other) const {
    State ret;
    ret.cnt = min(cnt, other.cnt);
    ret.ways = ((cnt == ret.cnt ? ways : 0) + (other.cnt == ret.cnt ? other.ways : 0)) % 67;
    return ret;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  string w = "shh";
  vector f(n + 1, vector(n + 1, vector<State>(3)));
  f[0][0][0] = {0, 1};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      for (int t = 0; t <= 2; t++) {
        for (char c = 'a'; c <= 'z'; c++) {
          int ni = i + 1;
          int nt = (c == w[t] ? t + 1 : (c == w[0] ? 1 : 0));
          int nj = j + int(nt == 3);
          nt %= 3;
          State ft = f[i][j][t];
          ft.cnt += int(c != s[i]);
          f[ni][nj][nt] = f[ni][nj][nt] + ft;
        }
      }
    }
  }
  State ans;
  for (int t = 0; t <= 2; t++) {
    ans = ans + f[n][k][t];
  }
  cout << ans.cnt << " " << ans.ways << '\n';
  return 0;
}
