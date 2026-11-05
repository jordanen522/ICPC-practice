#include <iostream>

using namespace std;

void solve() {
  int64_t xa, ya, xb, yb, xc, yc;
  cin >> xa >> ya >> xb >> yb >> xc >> yc;
  int64_t orig = xa*xa+ya*ya;
  int64_t bdist = (xb-xa)*(xb-xa)+(yb-ya)*(yb-ya);
  int64_t cdist = (xc-xa)*(xc-xa)+(yc-ya)*(yc-ya);
  if(bdist > orig || cdist > orig) return void(cout << "NO\n");
  if(bdist == orig && 2*xa==xb && 2*ya==yb) return void(cout << "NO\n");
  if(cdist == orig && 2*xa==xc && 2*ya==yc) return void(cout << "NO\n");
  if(bdist == orig && cdist == orig) return void(cout << "NO\n");
  cout << "YES\n";
}

int main() {
  int t;
  cin >> t;
  while(t--) solve();
}
