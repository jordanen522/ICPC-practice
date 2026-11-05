#include <iostream>

using namespace std;

int main() {
  int n;
  string s;
  cin >> n >> s;
  for(int i = 0; i < s.size(); i++) {
    if(s[i] == '2') {
      if(i > 0) s[i-1] = '0';
      if(i + 1 < s.size()) s[i+1] = '0';
    }
  }
  int ret = 0;
  for(int i = 0; i < s.size();) {
    if(s[i] != '1') {
      i++; continue;
    }
    int j = i+1;
    while(j < s.size() && s[j] == '1') j++;
    int amt = (j-i);
    i = j;
    ret += (amt+1)/2;
  }
  cout << ret << "\n";
}
