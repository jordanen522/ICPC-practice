#include <array>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, m, p;
  cin >> n >> m >> p;
  if(n == 1 && m == 1) return void(cout << (1%p) << "\n"), 0;
  if(n == 1 || m == 1) {
    int64_t ret = 1;
    for(int i = 2; i <= max(n, m); i++) {
      ret *= i;
      ret %= p;
    }
    cout << ret << "\n";
    return 0;
  }
  vector<vector<array<int64_t, 2>>> dp(n+1);
  for(auto& x: dp) x.assign(m+1, array<int64_t, 2>({0, 0}));
  dp[2][1][0] = 2 % p;
  dp[1][2][1] = 2 % p;
  for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
    if(i+1 <= n) {
      dp[i+1][j][0] += dp[i][j][1];
      dp[i+1][j][0] %= p;
    }
    if(j+1 <= m) {
      dp[i][j+1][1] += dp[i][j][1] * (i+j);
      dp[i][j+1][1] %= p;
    }
    if(i+1 <= n) {
      dp[i+1][j][0] += dp[i][j][0] * (i+j);
      dp[i+1][j][0] %= p;
    }
    if(j+1 <= m) {
      dp[i][j+1][1] += dp[i][j][0] * (i+j);
      dp[i][j+1][1] %= p;
    }
  }
  cout << (dp[n][m][0] + dp[n][m][1])%p << "\n";
}
