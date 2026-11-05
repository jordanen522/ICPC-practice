#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int unweighted = 0;
  double bonus = 0;
  for(int i = 0; i < n; i++) {
    string s;
    cin >> s;
    if(s[0] >= 'A' && s[0] <= 'C') {
      if(s[1] == '1') bonus += 0.05;
      if(s[1] == '2') bonus += 0.025;
    }
    if(s[0] == 'A') unweighted += 4;
    if(s[0] == 'B') unweighted += 3;
    if(s[0] == 'C') unweighted += 2;
    if(s[0] == 'D') unweighted += 1;
  }
  cout << fixed << setprecision(39) << ((unweighted/double(n)) + bonus) << "\n";
}
