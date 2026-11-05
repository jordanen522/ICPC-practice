#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
using namespace std;

int main() {
  int N, A;
  while (cin >> N) {
    vector<int> last(N+1);
    vector<tuple<int,int,int>> match;
    for (int x = 1; x <= N; x++) {
      cin >> A;
      if (last[A]) match.push_back({x-last[A], last[A], x});
      last[A] = x;
    }
    sort(match.begin(), match.end());

    int64_t ret = 0;
    map<int,int> sub;
    sub[1] = N;
    for (auto [_, x, y] : match) {
      auto it = sub.upper_bound(x);
      if (it == sub.begin()) continue;
      --it;
      if (it->second < y) continue;
      ret += int64_t(x - it->first + 1) * (it->second - y + 1) * (y-x);
      sub[x+1] = it->second;
      it->second = y-1;
    }
    cout << ret << endl;
  }
}
