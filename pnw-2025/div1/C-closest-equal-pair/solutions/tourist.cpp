/**
 *    author:  tourist
 *    created: 27.10.2025 20:09:08
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    --a[i];
  }
  int64_t ans = 0;
  int64_t sum = 0;
  vector<pair<int, int>> st = {{-1, -1}};
  vector<int> last(n, -1);
  for (int i = 0; i < n; i++) {
    if (last[a[i]] != -1) {
      pair<int, int> p = {i - last[a[i]], last[a[i]]};
      while (st.back().first >= p.first) {
        sum -= int64_t(st.back().second - st[st.size() - 2].second) * st.back().first;
        st.pop_back();
      }
      if (p.second > st.back().second) {
        sum += int64_t(p.second - st.back().second) * p.first;
        st.push_back(p);
      }
    }
    last[a[i]] = i;
    ans += sum;
  }
  cout << ans << '\n';
  return 0;
}
