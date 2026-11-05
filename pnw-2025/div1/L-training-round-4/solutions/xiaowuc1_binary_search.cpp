#include <array>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<array<int, 2>> v(n);
  auto valid = [&](int thresh) -> bool {
    int lhs = 0;
    int rhs = thresh;
    int amt = thresh;
    for(auto [a, b]: v) {
      lhs = max(lhs, a);
      rhs = min(rhs, amt - b);
      if(lhs > rhs) return false;
      amt++; rhs++;
    }
    return true;
  };
  for(auto& x: v) cin >> x[0] >> x[1];
  int lhs = 0;
  int rhs = 2.1e9;
  while(lhs < rhs) {
    int mid = lhs + (rhs - lhs) / 2;
    if(valid(mid)) rhs = mid;
    else lhs = mid + 1;
  }
  cout << lhs << "\n";
}
