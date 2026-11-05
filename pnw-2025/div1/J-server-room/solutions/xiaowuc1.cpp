#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int dx[4]{-1,0,1,0};
int dy[4]{0,1,0,-1};
const int MOD = 998244353;
int main() {
  int r, c;
  cin >> r >> c;
  vector<string> g(r);
  for(auto& x: g) cin >> x;
  if(c > r) {
    vector<string> ng(c);
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) {
      ng[j] += g[i][j];
    }
    swap(g, ng);
    swap(r, c);
  }
  for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) {
    if(g[i][j] == '2') {
      for(int k = 0; k < 4; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if(nx >= 0 && nx < r && ny >= 0 && ny < c) g[nx][ny] = '0';
      }
    }
  }
  unordered_map<int, array<int, 2>> dp;
  dp[0] = {0, 1};
  for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) {
    unordered_map<int, array<int, 2>> ndp;
    auto upd = [&](int k, array<int, 2> v) -> void {
      if(!ndp.count(k) || ndp[k][0] < v[0]) ndp[k] = v;
      else if(ndp[k][0] == v[0]) {
        ndp[k][1] += v[1];
        if(ndp[k][1] >= MOD) ndp[k][1] -= MOD;
      }
    };
    for(auto [k, v]: dp) {
      // do not use
      int nk = (k << 1) & ((1 << c) - 1);
      upd(nk, v);
      // use
      bool canuse = g[i][j] == '1';
      if((j > 0) && (k & 1)) canuse = false;
      if(k & (1 << (c - 1))) canuse = false;
      if(canuse) {
        nk |= 1;
        upd(nk, {v[0]+1, v[1]});
      }
    }
    swap(dp, ndp);
  }
  int amt = 0;
  int ret = 0;
  for(auto [k, v]: dp) {
    if(v[0] > amt) {
      amt = v[0];
      ret = 0;
    }
    if(v[0] == amt) {
      ret += v[1];
      if(ret >= MOD) ret -= MOD;
    }
  }
  cout << amt << " " << ret << "\n";
}
