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

    int n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    sort(all(a));
    ll lsum = 0, rsum = 0;
    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 1) {
            lsum += a[i / 2];
            rsum += a[i];
        } else {
            rsum += a[i] - a[i / 2];
        }
        ans[n - i - 1] = rsum - lsum;
    }
    for (auto x : ans) {
        cout << x << "\n";
    }
}