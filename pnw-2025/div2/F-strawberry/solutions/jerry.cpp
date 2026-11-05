#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
typedef int uci;
#define int long long
#define F first
#define S second
typedef complex<double> cd;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define irep(i, a, b) for(int i = a; i > (b); --i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
#define ve vector
typedef ve<int> vi;
typedef ve<vi> vvi;

struct debugger{
    template <typename T>
    debugger& operator<<(T &a){
        #ifdef DEBUG
            cerr << a;
        #endif
        return *this;
    }
    template <typename T>
    debugger& operator<<(T &&a){
        #ifdef DEBUG
            cerr << a;
        #endif
        return *this;
    }
} deb;

const double PI = acos(-1.0);
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

//! function insert

//THINK FIRST, CODE SECOND
//DON'T GET STUCK ON ONE STRATEGY
//CALM DOWNNN FOR ONCE IN YOUR LIFE
//REDUCE
//COUGH E??!?!?!! O.O
//uwu i see you ryan

void solve() {
    string s;
    cin >> s;

    int n;
    cin >> n;
    int out{};
    for(char c : s){
        int dist = c-'r';
        if(dist < 0)
            dist = 26 + dist;

        int left = n - dist;
        if(left > 0){
            out += left/26 + !!(left%26);
        }
    }

    cout << out << '\n';
}

uci main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

        // cout << "Case #" << t  << ": ";
        solve();
}

/*
    random number generator stuff
    num = rng(); gives integer number
    num = uniform_int_distribution<int>(a, b)(rng); -> bounds [a, b]
    num = uniform_real_distribution<double>(a, b)(rng); -> bounds [a, b)
    can also instantiate distributions and call on generator:
    uniform_int_distribution<int> thing(a, b);
    num = thing(rng);
*/
// struct custom_hash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = lrng();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };
