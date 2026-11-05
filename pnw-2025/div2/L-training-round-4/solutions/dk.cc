#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int N, I, T;
  while (cin >> N) {
    int ret = 0, i = 0, t = 0, free = 0;
    for (int n = 0; n < N; n++) {
      cin >> I >> T;
      int i2 = max(i, I), t2 = max(t, T);
      int diff = i2-i + t2-t, f = min(diff, free);
      ret += diff-f;
      free += 1-f;
      i = i2; t = t2;
    }
    cout << ret << endl;
  }
}
