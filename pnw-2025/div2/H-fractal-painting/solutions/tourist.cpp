/**
 *    author:  tourist
 *    created: 28.10.2025 13:24:51
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
struct TPoint {
  T x = 0;
  T y = 0;

  inline TPoint operator-(const TPoint& rhs) const { return TPoint(x - rhs.x, y - rhs.y); }

  inline T abs2() const {
    return x * x + y * y;
  }

  bool operator ==(const TPoint& other) const {
    return x == other.x && y == other.y;
  }
};

using Point = TPoint<int64_t>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    Point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    auto da = a.abs2();
    auto db = (b - a).abs2();
    auto dc = (c - a).abs2();
    if (db > da || dc > da || (db == da && dc == da) || b - a == a || c - a == a) {
      cout << "NO" << '\n';
    } else {
      cout << "YES" << '\n';
    }
  }
  return 0;
}
