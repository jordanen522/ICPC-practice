#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  int64_t d, m;
  cin >> n >> d >> m;
  m *= d;
  vector<int64_t> v(n);
  for(auto& x: v) cin >> x;
  sort(v.begin(), v.end());
  int64_t tot = 0;
  int64_t pen = 0;
  for(int i = 0; i < n; i++) {
    pen += tot;
    if(d * (i+1) - pen >= m) {
      return cout << i+1 << "\n", 0;
    }
    tot += v[i];
  }
  cout << "-1\n";  
}
