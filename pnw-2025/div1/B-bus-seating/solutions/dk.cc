#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  int N, K, M, C, A;
  while (cin >> N >> K >> M >> C) {
    vector<set<int>> v(K);
    int sk = 0;
    for (int r = 1; r <= N; r++) v[0].insert(r);
    for (int i = 0; i < M; i++) {
      cin >> A;
      int bestr = -1, bestk = -1, bestv = 0;
      for (int k = sk; k < K && C >= bestv; k++, bestv <<= 1) {
        int r1 = -1, r2 = -1;
        auto it = v[k].lower_bound(A);
        if (it != v[k].end()) r2 = *it;
        if (it != v[k].begin()) r1 = *--it;
        for (int r : {r1, r2}) if (r != -1) {
          int v = C - abs(A-r);
          if (v > bestv || (v == bestv && r < bestr)) { bestr = r; bestk = k; bestv = v; }
        }
      }
      if (i) cout << ' ';
      cout << bestr;
      v[bestk].erase(bestr);
      if (bestk+1 < K) v[bestk+1].insert(bestr);
      if (v[sk].empty()) sk++;
    }
    cout << endl;
  }
}
