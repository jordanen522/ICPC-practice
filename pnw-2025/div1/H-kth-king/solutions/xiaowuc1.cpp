#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int64_t> v(n);
  for(auto& x: v) cin >> x;
  sort(v.begin(), v.end());
  vector<int64_t> ret(n);
  int64_t lhs = 0, rhs = 0;
  for(int q = 1; q < n; q++) {
    rhs += v[q];
    if(q%2) lhs += v[q/2];
    else rhs -= v[q/2];
    ret[n-1-q] = rhs-lhs;
  }
  for(int i = 0; i < n; i++) cout << ret[i] << "\n";
}
