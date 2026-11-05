#include <array>
#include <iostream>
#include <vector>

using namespace std;

const string WANT = "shh";
const int64_t MOD = 67;
int getnext(const string& s) {
  for(int len = min(s.size(), WANT.size()); len > 0; len--) {
    if(s.substr(s.size() - len) == WANT.substr(0, len)) {
      return len;
    }
  }
  return 0;
}
int main() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  vector<array<array<int64_t, 2>, 3>> dp(k+1);
  for(auto& x: dp) for(auto& y: x) y = {(int64_t)1e9, (int64_t)1e9};
  dp[0][0] = {0, 1};
  for(int i = 0; i < n; i++) {
    vector<array<array<int64_t, 2>, 3>> ndp(k+1);
    auto upd = [&](int x, int y, int nchange, int64_t nways) -> void {
      if(nchange < ndp[x][y][0]) {
        ndp[x][y][0] = nchange;
        ndp[x][y][1] = 0;
      }
      if(nchange == ndp[x][y][0]) {
        ndp[x][y][1] += nways;
        if(ndp[x][y][1] >= MOD) ndp[x][y][1] -= MOD;
      }
    };
    for(auto& x: ndp) for(auto& y: x) y = {(int64_t)1e9, (int64_t)1e9};
    for(int a = 0; a <= k; a++) for(int b = 0; b < 3; b++) {
      if(dp[a][b][0] == 1e9) continue;
      string have = WANT.substr(0, b);
      for(char c = 'a'; c <= 'z'; c++) {
        string nhave = have;
        nhave += c;
        int na = a;
        int nb = getnext(nhave);
        int nchange = dp[a][b][0] + (c != s[i]);
        int64_t nways = dp[a][b][1];
        if(nb == 3) {
          na++; nb = 0;
        }
        if(na <= k) {
          upd(na, nb, nchange, nways);
        }
      }
    }
    swap(dp, ndp);
  }
  int64_t minchange = 1e9;
  int64_t minways = 0;
  for(int i = 0; i < 3; i++) {
    if(dp[k][i][0] < minchange) {
      minchange = dp[k][i][0];
      minways = 0;
    }
    if(dp[k][i][0] == minchange) {
      minways += dp[k][i][1];
      if(minways >= MOD) minways -= MOD;
    }
  }
  cout << minchange << " " << minways << "\n";
}
