#include <array>
#include <iostream>

using namespace std;

int main() {
  array<int, 26> appears; appears.fill(0);
  string s;
  cin >> s;
  for(auto c: s) {
    int idx = c - 'r';
    if(idx < 0) idx += 26;
    appears[idx]++;
  }
  int64_t ret = 0;
  int64_t n;
  cin >> n;
  for(int i = 0; i < 26; i++) {
    ret += ((n/26) + (n%26 > i)) * appears[i];
  }
  cout << ret << "\n";
}
