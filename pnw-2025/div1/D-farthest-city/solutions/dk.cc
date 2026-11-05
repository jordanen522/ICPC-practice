#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
  int N, A, B, D;
  while (cin >> N) {
    vector<vector<int>> g(N+1), gd(N+1), gi(N+1), ge(N+1);
    for (int i = 0; i < N; i++) {
      cin >> A >> B >> D;
      ge[A].push_back(2*i);
      ge[B].push_back(2*i+1);
      gi[A].push_back(g[B].size());
      gi[B].push_back(g[A].size());
      g[A].push_back(B);
      g[B].push_back(A);
      gd[A].push_back(D);
      gd[B].push_back(D);
    }

    vector<int> pred(N+1), predd(N+1), cyc, cycd, gcyc(N+1, false);
    function<void(int,int,int)> getCyc = [&](int x, int p, int d) {
      if (cyc.size()) return;
      if (pred[x]) {
        cyc.push_back(x); cycd.push_back(d);
        do { cyc.push_back(p); cycd.push_back(predd[p]); p = pred[p]; } while (p != x);
        return;
      }
      pred[x] = p; predd[x] = d;
      for (int i = 0; i < g[x].size(); i++) if (g[x][i] != p) getCyc(g[x][i], x, gd[x][i]);
    };
    getCyc(1, -1, 0);
    for (int i = 0; i < cyc.size(); i++) gcyc[cyc[i]] = true;

    vector<int64_t> mx(N+1), outer(N+1), memo(7*N, -1);
    function<int64_t(int,int,int,int,int)> rec = [&](int x, int i, int px, int pi, int e) -> int64_t {
      int64_t& cur = memo[e];
      if (cur != -1) return cur;
      cur = 0;
      if (gcyc[x] && i == 0) cur = outer[x];
      for (int y, j, d, ei = 0; ei < 3; ei++) {
        if (ei == 0) { y = x; j = i-1; d = 0; }
        if (ei == 1) { y = x; j = i+1; d = 0; }
        if (ei == 2) { y = g[x][i]; j = gi[x][i]; d = gd[x][i]; }
        if (y == px && j == pi) continue;
        if (j < 0 || j >= g[y].size()) continue;
        if (x != y && gcyc[x] && gcyc[y]) continue;
        cur = max(cur, rec(y, j, x, i, 3*ge[x][i]+ei) + d);
      }
      mx[x] = max(mx[x], cur);
      return cur;
    };
    for (int x = 1; x <= N; x++) rec(x, 0, -1, -1, 6*N+x-1);

    multiset<int64_t> ls, rs;
    int64_t ladd = 0, radd = 0, ld = 0, rd = 0;
    for (int j = cyc.size()-1; j >= 0; j--) { rd += cycd[j]; rs.insert(rd + mx[cyc[j]]); }
    for (int i = 0, j = 0; i < cyc.size(); i++) {
      while (ld < rd) {
        rs.erase(rs.find(rd + mx[cyc[j]] - radd));
        ls.insert(ld + mx[cyc[j]] - ladd);
        ld += cycd[j]; rd -= cycd[j];
        j = (j+1)%cyc.size();
      }
      ls.erase(ls.find(mx[cyc[i]] - ladd));
      if (ls.size()) outer[cyc[i]] = max(outer[cyc[i]], *ls.rbegin() + ladd);
      if (rs.size()) outer[cyc[i]] = max(outer[cyc[i]], *rs.rbegin() + radd);
      rs.insert(mx[cyc[i]] - radd);
      ld -= cycd[i]; rd += cycd[i];
      ladd -= cycd[i]; radd += cycd[i];
    }

    memo = vector<int64_t>(7*N, -1);
    for (int x = 1; x <= N; x++) {
      rec(x, 0, -1, -1, 6*N+x-1);
      cout << mx[x];
      if (x < N) cout << ' '; else cout << endl;
    }
  }
}
