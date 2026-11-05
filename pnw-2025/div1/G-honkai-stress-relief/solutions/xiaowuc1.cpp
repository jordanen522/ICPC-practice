#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  double ret = 1;
  while(n--) {
    int lhs, rhs;
    cin >> lhs >> rhs;
    lhs = max(lhs, a);
    rhs = min(rhs, b);
    if(lhs > rhs) ret = 0;
    else ret *= (rhs - lhs) / double(b-a);
  }
  cout << fixed << setprecision(39) << (1-ret) << "\n";
}
