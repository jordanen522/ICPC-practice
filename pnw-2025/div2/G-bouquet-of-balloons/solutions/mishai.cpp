#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define smx(a, b) a = max(a, b)
#define smn(a, b) a = min(a, b)
#define pb push_back
#define endl '\n'

const ll INF = 1e12 + 5;

const ll MOD = 1e9 + 7;
const ld EPS = 1e-9;

mt19937 rng(time(0));

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, d, m; cin >> n >> d >> m;
    m *= d;
    vector<int> s(n);
    rep(i,0,n) cin >> s[i];
    sort(all(s));
    ll sum = 0;
    ll val = 0;
    for (int i = 0; i < n; i++) {
        val += d - sum;
        if (val >= m) {
            cout << (i + 1) << "\n";
            return 0;
        }
        sum += s[i];
    }
    cout << "-1\n";
    return 0;
}