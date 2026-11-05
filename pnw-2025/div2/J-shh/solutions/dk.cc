#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int64_t MOD = 67;

int main() {
  int N, K;
  while (cin >> N >> K) {
    string S;
    cin >> S;
    vector<pair<int,int64_t>> memo(1<<(7+5+2), {200,0});
    function<pair<int,int64_t>(int,int,int)> doit = [&](int i, int k, int shh) -> pair<int,int64_t> {
      if (k > K) return {100,0};
      if (i == N) return k == K ? pair<int,int>{0,1} : pair<int,int>{100,0};
      pair<int,int64_t>& ret = memo[(i<<(5+2))+(k<<2)+shh];
      if (ret.first != 200) return ret;
      for (char ch = 'a'; ch <= 'z'; ch++) {
        int i2 = i+1, k2 = k, shh2 = (ch == 's');
        if (ch == 'h' && shh) shh2 = shh+1;
        if (shh2 == 3) { shh2 = 0; k2++; }
        pair<int,int64_t> cur = doit(i2, k2, shh2);
        if (ch != S[i]) cur.first++;
        if (cur.first == ret.first) ret.second = (ret.second + cur.second) % MOD;
        if (cur.first < ret.first) ret = cur;
      }
      return ret;
    };
    pair<int,int64_t> ret = doit(0, 0, 0);
    cout << ret.first << ' ' << ret.second << endl;
  }
}
