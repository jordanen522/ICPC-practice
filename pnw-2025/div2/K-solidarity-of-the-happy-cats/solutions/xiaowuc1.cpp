#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> radiusv(n), typev(n);
  for(int i = 0; i < n; i++) cin >> radiusv[i] >> typev[i];
  for(int i = 0; i < n; i++) typev[i]--;
  vector<string> g(m);
  for(int i = 0; i < m; i++) cin >> g[i];
  vector<int64_t> dp(n);
  iota(dp.begin(), dp.end(), 0);
  for(int i = 0; i < n; i++) for(int j = i+1; j < n; j++) {
    if(g[typev[i]][typev[j]] == '0') dp[j] = max(dp[j], dp[i] + radiusv[j] + 1);
    if(g[typev[j]][typev[i]] == '0') dp[j] = max(dp[j], dp[i] + radiusv[i] + 1);
    dp[j] = max(dp[j], dp[i] + j - i);
  }
  cout << (dp[n-1]+1) << "\n";
}
