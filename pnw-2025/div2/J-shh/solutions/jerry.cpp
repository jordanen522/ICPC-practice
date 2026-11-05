#include <bits/stdc++.h>

using namespace std;

// thank you geothermal :goat:
void __deb(int t) {cerr << t;}
void __deb(long t) {cerr << t;}
void __deb(long long t) {cerr << t;}
void __deb(unsigned int t) {cerr << t;}
void __deb(unsigned long t) {cerr << t;}
void __deb(unsigned long long t) {cerr << t;}
void __deb(float t) {cerr << t;}
void __deb(double t) {cerr << t;}
void __deb(long double t) {cerr << t;}
void __deb(char t) {cerr << '\'' << t << '\'';}
void __deb(const char *t) {cerr << '\"' << t << '\"';}
void __deb(const string &t) {cerr << '\"' << t << '\"';}
void __deb(bool t) {cerr << (t ? "true" : "false");}
template<typename T, typename V>
void __deb(const pair<T, V> &x){ cerr << '{'; __deb(x.first); cerr << ", "; __deb(x.second); cerr << '}'; }
template<typename T>
void __deb(const T &x){
    int f = 0; cerr << '{'; 
    for(auto &i: x){ if(f++) cerr << ", "; __deb(i);}
    cerr << "}";
}
void _rdeb(vector<string> &names, int ind){}
template<typename T, typename... V>
void _rdeb(vector<string> &names, int ind, T t, V... v){
    if(ind != 0) cerr << "==============\n";
    cerr << names[ind] << '\n'; __deb(t); cerr << '\n';
    _rdeb(names, ind+1, v...);
}
template<typename... V>
void _deb(string vars, V... v){
    vector<string> names(1); int in{};
    for(char c : vars)
        if(c == ',' && in == 0){
            while(names.back().size() && isspace(names.back().back())) names.back().pop_back();
            names.push_back("");
        }else{
            if(c == '(') in++; if(c == ')') in--;
            if(!isspace(c) || names.back().size()) names.back().push_back(c);
        }
    while(names.back().size() && isspace(names.back().back())) names.back().pop_back();
    _rdeb(names, 0, v...);
}
#ifdef DEBUG
#define deb(x...) {                              \
    cerr << __func__ << ':' << __LINE__ << '\n'; \
    _deb(#x, x);                                 \
    cerr << '\n';                                \
}
#define debsep(x...) {                           \
    cerr << __func__ << ':' << __LINE__ << '\n'; \
    _deb(#x, x);                                 \
    cerr << "****************************\n";    \
}
#else
#define deb(x...)
#define debsep(x...)
#endif

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
const int MOD = 67;
const int INF = 1e9;
const ll LINF = 1e18;

//! function insert

//THINK FIRST, CODE SECOND
//DON'T GET STUCK ON ONE STRATEGY
//CALM DOWNNN FOR ONCE IN YOUR LIFE
//REDUCE
//COUGH E??!?!?!! O.O
//uwu i see you ryan

void get(int& a, int b, int mult = 1){
    if(b == -1)
        return;
    int c = (b*mult)%MOD;
    if(a == -1)
        a = c;
    else{
        a += c;
        a %= MOD;
    }
}

void solve() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;
    s = string(1, ' ') + s;

    // 0 - accum
    // 1 - s
    // 2 - h
    // 3 - h2 also used as keeping as end of thing
    // [# to change, # of ways]
    int lim = k+2;
    // index, cost, k amt, special index
    ve<ve<ve<ve<int>>>> dp(n+1, ve<ve<ve<int>>>(n+1, ve<ve<int>>(lim, ve<int>(4, -1))));

    dp[0][0][0][0] = 1;
    // j / 3 is number of shh currently
    for(int i{1}; i <= n; ++i){
        for(int c{}; c <= n; ++c){
            for(int j = 0; j < lim; ++j){
                int adds, mult;
                // handle 0 - accum
                adds = (s[i] == 's') ? 1 : 0;
                mult = (s[i] == 's') ? 25 : 1;
                if(j > 0 && c-adds >= 0)
                    get(dp[i][c][j][0], dp[i-1][c-adds][j-1][3], mult);
                if(c-adds >= 0)
                    get(dp[i][c][j][0], dp[i-1][c-adds][j][0], mult);
                adds = (s[i] == 's') || (s[i] == 'h') ? 1 : 0;
                mult = (s[i] == 's') || (s[i] == 'h') ? 24 : 1;
                if(c-adds >= 0)
                    get(dp[i][c][j][0], dp[i-1][c-adds][j][1], mult);
                adds = (s[i] == 's') || (s[i] == 'h') ? 1 : 0;
                mult = (s[i] == 's') || (s[i] == 'h') ? 24 : 1;
                if(c-adds >= 0)
                    get(dp[i][c][j][0], dp[i-1][c-adds][j][2], mult);

                // handle 1 - s
                adds = (s[i] == 's') ? 0 : 1;
                if(j > 0 && c-adds >= 0)
                    get(dp[i][c][j][1], dp[i-1][c-adds][j-1][3]);
                if(c-adds >= 0)
                    get(dp[i][c][j][1], dp[i-1][c-adds][j][0]);
                if(c-adds >= 0)
                    get(dp[i][c][j][1], dp[i-1][c-adds][j][1]);
                if(c-adds >= 0)
                    get(dp[i][c][j][1], dp[i-1][c-adds][j][2]);

                // handle 2 - h
                adds = (s[i] == 'h') ? 0 : 1;
                if(c-adds >= 0)
                    get(dp[i][c][j][2], dp[i-1][c-adds][j][1]);

                // handle 3 - h
                adds = (s[i] == 'h') ? 0 : 1;
                if(c-adds >= 0)
                    get(dp[i][c][j][3], dp[i-1][c-adds][j][2]);
            }
        }
    }

    vi amts(n+1, -1);

    for(int i{}; i <= n; ++i){
        get(amts[i], dp[n][i][k][0]);
        get(amts[i], dp[n][i][k][1]);
        get(amts[i], dp[n][i][k][2]);
        if(k > 0)
            get(amts[i], dp[n][i][k-1][3]);
    }

    for(int i{}; i <= n; ++i){
        if(amts[i] != -1){
            cout << i << ' ' << amts[i] << '\n';
            return;
        }
    }
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
