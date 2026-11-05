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

    int n, k, m; ll C; cin >> n >> k >> m >> C;
    vector<int> a(m);
    rep(i,0,m) cin >> a[i];
    vector<set<int>> open(k);
    for (int i = 1; i <= n; i++) {
        open[0].insert(i);
    }
    int fo = 0;
    for (int i = 0; i < m; i++) {
        while (sz(open[fo]) == 0) ++fo;
        int mlevel = MOD, mpos = MOD;
        for (int level = fo; level < min(k, fo + 30); level++) {
            if (sz(open[level]) != 0) {
                auto it = open[level].lower_bound(a[i]);
                int pos = MOD;
                if (it != open[level].end()) {
                    pos = *it;
                }
                if (it != open[level].begin()) {
                    --it;
                    if (abs(a[i] - *it) <= abs(a[i] - pos)) {
                        pos = *it;
                    }
                }
                if (mlevel == MOD) {
                    mlevel = level;
                    mpos = pos;
                } else {
                    int dd = level - mlevel;
                    ll c1 = (C - abs(mpos - a[i])) << dd;
                    ll c2 = (C - abs(pos - a[i]));
                    if (c1 < c2 || (c1 == c2 && pos < mpos)) {
                        mlevel = level;
                        mpos = pos;
                    }
                }
            }
        }
        assert(mlevel != MOD);
        open[mlevel].erase(mpos);
        if (mlevel < k - 1) {
            open[mlevel + 1].insert(mpos);
        }
        cout << mpos << " ";
    }
    cout << "\n";


    return 0;
}