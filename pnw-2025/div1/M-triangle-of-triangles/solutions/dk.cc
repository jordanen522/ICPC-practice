#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int main() {
  int T, A1, B1, C1, A2, B2, C2, A3, B3, C3;
  for (cin >> T; T--;) {
    cin >> A1 >> B1 >> C1 >> A2 >> B2 >> C2 >> A3 >> B3 >> C3;
    bool pass = false;
    multiset<int> m2{A2, B2, C2}, m3{A3, B3, C3};
    for (int i = 0; i < 3; i++, swap(A1, B1), swap(B1, C1)) {
      for (int deg = 5; deg < A1; deg++) {
        multiset<int> t1{deg, B1, 180-deg-B1};
        multiset<int> t2{A1-deg, C1, 180-(A1-deg)-C1};
        if ((t1 == m2 || t1 == m3) && (t2 == m2 || t2 == m3)) pass = true;
      }
    }
    cout << (pass ? "YES" : "NO") << endl;
  }
}
