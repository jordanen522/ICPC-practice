#include <iostream>
using namespace std;

int main() {
  int T, X0, Y0, X1, Y1, X2, Y2;
  for (cin >> T; T--;) {
    cin >> X0 >> Y0 >> X1 >> Y1 >> X2 >> Y2;
    int len0 = X0*X0 + Y0*Y0;
    int len1 = (X1-X0)*(X1-X0) + (Y1-Y0)*(Y1-Y0);
    int len2 = (X2-X0)*(X2-X0) + (Y2-Y0)*(Y2-Y0);
    if (len1 > len0 || len2 > len0) { cout << "NO" << endl; continue; }
    if (len1 == len0 && len2 == len0) { cout << "NO" << endl; continue; }
    if (X1 == 2*X0 && Y1 == 2*Y0) { cout << "NO" << endl; continue; }
    if (X2 == 2*X0 && Y2 == 2*Y0) { cout << "NO" << endl; continue; }
    cout << "YES" << endl;
  }
}
