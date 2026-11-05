#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, Q;
  while (cin >> N >> Q) {
    vector<vector<int>> g(N+1, {0}), ftoy(N+1, vector<int>(51));
    vector<int> toy(N+1);
    ftoy[0][0] = N;
    for (int q = 0; q < Q; q++) {
      char ch;
      int i, j;
      cin >> ch;
      if (ch == 'F') {
        cin >> i >> j;
        g[i].push_back(j);
        g[j].push_back(i);
        ftoy[j][toy[i]]++;
        ftoy[i][toy[j]]++;
      } else if (ch == 'A') {
        cin >> i;
        for (auto j : g[i]) { ftoy[j][toy[i]]--; ftoy[j][toy[i]+1]++; }
        toy[i]++;
      } else {
        cin >> j;
        int ret = 50;
        for (; ret >= 0; ret--) if (ftoy[0][ret] != ftoy[j][ret] + (toy[j]==ret)) break;
        cout << ret << endl;
      }
    }
  }
}
