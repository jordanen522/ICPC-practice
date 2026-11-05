#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  while (cin >> N) {
    vector<int64_t> v(N);
    for (auto& x : v) cin >> x;
    sort(v.begin(), v.end());
    int64_t lsum = 0, rsum = 0;
    for (int i = 0; i < N/2; i++) lsum += v[i];
    for (int i = N/2; i < N; i++) rsum += v[i];
    for (int sz = N; sz >= 1; sz--) {
      cout << ((sz/2) * v[sz/2] - lsum) + (rsum - (sz+1)/2 * v[sz/2]) << endl;
      if (sz%2 == 0) { lsum -= v[sz/2-1]; rsum += v[sz/2-1]; }
      rsum -= v[sz-1];
    }
  }
}
