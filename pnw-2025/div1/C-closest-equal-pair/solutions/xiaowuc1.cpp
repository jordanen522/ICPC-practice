#include <array>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> v(n);
  for(auto& x: v) cin >> x;
  int64_t ret = 0;
  vector<int> lhs(n+1, 1e9);
  vector<array<int, 2>> st;
  st.push_back({-1, -1});
  int64_t contrib = 0;
  for(int i = 0; i < n; i++) {
    if(lhs[v[i]] < i) {
      array<int, 2> curr = {i - lhs[v[i]], lhs[v[i]]};
      while(curr[0] <= st.back()[0]) {
        auto [x, idx] = st.back(); st.pop_back();
        auto [_, lidx] = st.back();
        contrib -= x * int64_t(idx - lidx);
      }
      if(lhs[v[i]] > st.back()[1]) {
        contrib += curr[0] * int64_t(lhs[v[i]] - st.back()[1]);
        st.push_back(curr);
      }
    }
    lhs[v[i]] = i;
    ret += contrib;
  }
  cout << ret << "\n";
}
