#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> adj(n);
  vector<array<int, 51>> dp(n);
  vector<int> toys(n);
  array<int, 51> toycount = {0};
  toycount[0] = n;
  while(q--) {
    char c;
    cin >> c;
    if(c == 'F') {
      int i, j;
      cin >> i >> j; 
      i--;j--;
      adj[i].push_back(j);
      adj[j].push_back(i);
      dp[i][toys[j]]++;
      dp[j][toys[i]]++;
    }
    else if(c == 'A') {
      int idx;
      cin >> idx; 
      idx--;
      toycount[toys[idx]]--;
      toycount[toys[idx]+1]++;
      for(auto out: adj[idx]) {
        dp[out][toys[idx]]--;
        dp[out][toys[idx]+1]++;
      }
      toys[idx]++;
    }
    else if(c == 'Q') {
      int idx;
      cin >> idx;
      idx--;
      if(adj[idx].size() == n-1) {
        cout << "-1\n"; continue;
      }
      int ret = 50;
      while(ret >= 0) {
        if(toycount[ret] - dp[idx][ret] - (ret == toys[idx])) {
          cout << ret << "\n";
          break;
        }
        ret--;
      }
      if(ret < 0) cout << ret << "\n";
    }
    else assert(false);
  }
}
