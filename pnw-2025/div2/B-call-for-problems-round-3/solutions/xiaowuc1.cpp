#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, t;
  cin >> n >> t;
  vector<int> v(n);
  for(auto& x: v) cin >> x;
  sort(v.begin(), v.end());
  int ret = 1;
  int lhs = v[0];
  for(int i = 1; i < n; i++) {
    if(v[i] - lhs >= t) {
      ret++;
      lhs = v[i];
    }
  }
  cout << ret << "\n";
}
