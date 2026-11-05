#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  int aa = 0, bb = 0;
  int extra = 0;
  auto inc = [&](int& x, int want) -> void {
    assert(x < want);
    int use = min(want - x, extra);
    extra -= use; x += use;
    x = max(x, want);
  };
  for(int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    if(a > aa) inc(aa, a);
    if(b > bb) inc(bb, b);
    extra++;
    // cerr << i << " " << aa << " " << bb << " " << extra << endl;
  }
  cout << (aa+bb+extra-n) << "\n";
}
