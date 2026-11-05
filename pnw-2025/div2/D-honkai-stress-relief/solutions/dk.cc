#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  int N, A, B, S, E;
  while (cin >> N >> A >> B) {
    double ret = 1.0;
    for (int i = 0; i < N; i++) {
      cin >> S >> E;
      ret *= max(0, min(B,E)-max(A,S)) / double(B-A);
    }
    cout << fixed << setprecision(10) << 1.0-ret << endl;
  }
}
