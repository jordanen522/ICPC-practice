#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

bool equivalent(array<int, 3> a, array<int, 3> b) {
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  return a == b;
}
bool can(array<int, 3> have, array<int, 3> a, array<int, 3> b) {
  do {
    sort(b.begin(), b.end());
    do {
      if(a[0] + b[0] != 180) continue;
      array<int, 3> tri = {a[1], b[1], a[2] + b[2]};
      if(equivalent(have, tri)) return true;
    }
    while(next_permutation(b.begin(), b.end()));
  }
  while(next_permutation(a.begin(), a.end()));
  return false;
}
void rsolve() {
  array<int, 3> have;
  for(auto& x: have) cin >> x;
  array<int, 3> a, b;
  for(auto& x: a) cin >> x;
  for(auto& x: b) cin >> x;
  if(can(have, a, a) || can(have, a, b) || can(have, b, b)) return void(cout << "YES\n");
  cout << "NO\n";
}
int main() {
  int t;
  cin >> t;
  while(t--) rsolve();
}
