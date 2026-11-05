#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MOD 998244353

int main() {
  int X, Y;
  while (cin >> Y >> X) {
    vector<string> g(Y);
    for (auto& s : g) cin >> s;
    int sz = (1<<min(X,Y));
    vector<pair<int,int>> cnt(sz);
    auto add = [](pair<int,int>& a, int n, int c) {
      if (n > a.first) {
        a.first = n; a.second = c;
      } else if (n == a.first) {
        a.second = (a.second+c)%MOD;
      }
    };
    cnt[0] = {1, 1};
    for (int x = 0, y = 0, nextrow = 1; x < X && y < Y;) {
      vector<pair<int,int>> cnt2(1<<min(X,Y));
      for (int b = 0; b < cnt.size(); b++) {
        auto [n, c] = cnt[b];
        if (n == 0) continue;
        if (g[y][x] != '2') add(cnt2[b>>1], n, c);
        if (g[y][x] != '0' && !(b&1) && (nextrow || !(b&(sz/2)))) add(cnt2[(b>>1)+sz/2], n+(g[y][x]=='1'), c);
      }
      cnt.swap(cnt2);
      nextrow = 0;
      if (X < Y) {
        if (++x == X) { x = 0; ++y; nextrow = 1; }
      } else {
        if (++y == Y) { y = 0; ++x; nextrow = 1; }
      }
    }
    pair<int, int> ret{0, 0};
    for (auto [n, c] : cnt) add(ret, n, c);
    cout << ret.first-1 << ' ' << ret.second << endl;
  }
}
