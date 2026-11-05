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

ve<ar<int, 2>> cycle;
ve<ar<int, 2>> st;
bool onst[300001];
bool vis[300001];
bool dfs(int v, int c, int p, ve<ve<ar<int, 2>>> &adj){
    onst[v] = true;
    vis[v] = true;
    st.push_back({v, c});

    for(auto [u, w] : adj[v]){
        if(u == p)
            continue;
        if(onst[u]){
            cycle.push_back({u, w});
            while(st.back()[0] != u){
                cycle.push_back(st.back());
                st.pop_back();
            }
            return true;
        }else if(!vis[u]){
            if(dfs(u, w, v, adj))
                return true;
        }
    }

    st.pop_back();
    onst[v] = false;
    return false;
}
bool oncy[300001];

int getdeep(int v, int p, int d, ve<ve<ar<int, 2>>> &adj){
    int ret = d;
    for(auto [u, w] : adj[v]){
        if(oncy[u] || u == p)
            continue;
        ret = max(ret, getdeep(u, v, d+w, adj));
    }
    return ret;
}

void update(int v, int val, int l, int r, int lq, int rq, ve<ar<int, 2>> &seg){
    if(l > r || lq > r || rq < l)
        return;
    else if(lq <= l && r <= rq){
        seg[v][0] += val;
        seg[v][1] += val;
    }else{
        int mid = l + (r-l)/2;
        if(seg[v][1] != 0){
            update(v*2, seg[v][1], l, mid, l, mid, seg);
            update(v*2+1, seg[v][1], mid+1, r, mid+1, r, seg);
            seg[v][1] = 0;
            seg[v][0] = max(seg[v*2][0], seg[v*2+1][0]);
        }

        update(v*2, val, l, mid, lq, rq, seg);
        update(v*2+1, val, mid+1, r, lq, rq, seg);
        seg[v][0] = max(seg[v*2][0], seg[v*2+1][0]);
    }
}

int query(int v, int l, int r, int lq, int rq, ve<ar<int, 2>> &seg){
    if(l > r || lq > r || rq < l)
        return -INF;
    else if(lq <= l && r <= rq)
        return seg[v][0];
    else{
        int mid = l + (r-l)/2;
        if(seg[v][1] != 0){
            update(v*2, seg[v][1], l, mid, l, mid, seg);
            update(v*2+1, seg[v][1], mid+1, r, mid+1, r, seg);
            seg[v][1] = 0;
            seg[v][0] = max(seg[v*2][0], seg[v*2+1][0]);
        }
        return max(query(v*2, l, mid, lq, rq, seg), query(v*2+1, mid+1, r, lq, rq, seg));
    }
}
int out[300001];

struct dist{
    int val;
    int from;
    dist(int a, int b){
        val = a;
        from = b;
    }
    dist(){
        val = -INF;
        from = -1;
    }
    bool operator>(const dist& other) const {
        return val > other.val;
    }
    bool operator<(const dist& other) const {
        return val < other.val;
    }
    bool operator==(const dist& other){
        return val == other.val;
    }
};

ar<dist, 2> dp[300001];
dist preproc(int v, int p, ve<ve<ar<int, 2>>> &adj){
    dist ret(0, v);

    for(auto [u, c] : adj[v]){
        if(u == p || oncy[u])
            continue;
        dist t = preproc(u, v, adj);
        t.val += c;

        if(t > dp[v][0]){
            swap(dp[v][0], dp[v][1]);
            dp[v][0] = t;
        }else if(t > dp[v][1]){
            dp[v][1] = t;
        }

        if(t > ret)
            ret = t;
    }
    ret.from = v;
    return ret;
}

void reroot(int v, int p, dist fromp, ve<ve<ar<int, 2>>> &adj){
    out[v] = max(fromp.val, dp[v][0].val);

    for(auto [u, c] : adj[v]){
        if(u == p || oncy[u])
            continue;
        dist t = fromp;
        t.val += c;
        dist tt = dp[v][0].from == u ? dp[v][1] : dp[v][0];
        tt.val += c;
        reroot(u, v, max(t, tt), adj);
    }
}

void solve() {
    int n;
    cin >> n;

    ve<ve<ar<int, 2>>> adj(n);
    rep(i, 0, n){
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    // find cycle
    dfs(0, 0, -1, adj);
    reverse(all(cycle));
    int cytot{};
    for(auto [u, c] : cycle){
        oncy[u] = true;
        cytot += c;
    }

    for(int i{}; i < n; ++i){
        vis[i] = false;
    }

    // find deepest leaf at each cycle node
    int m = sz(cycle);
    vi costs(m);
    int ind{};
    for(auto [u, c] : cycle){
        costs[ind] = getdeep(u, -1, 0, adj);
        ind++;
    }
    deb(costs);

    vi othertrees(m, -INF);
    // scan left and find best for each
    // cycle is
    // {u, x} {v, u->v} {w, v->w}
    vi pre(2*m);
    for(int i{1}; i < 2*m; ++i){
        pre[i] = pre[i-1] + cycle[i%m][1];
    }
    deb(cycle);
    deb(pre);
    int lb = 0;
    ve<ar<int, 2>> seg(8*m);
    for(int i{}; i < 2*m; ++i){
        while(lb < i && 2*(pre[i] - pre[lb]) > cytot){
            lb++;
        }
        deb(i, lb);
        
        int ret = query(1, 0, 2*m-1, lb, i-1, seg);
        if(ret >= 0){
            othertrees[i%m] = ret;
        }
        update(1, costs[i%m], 0, 2*m-1, i, i, seg);
        update(1, cycle[(i+1)%m][1], 0, 2*m-1, lb, i, seg);
    }
    deb(othertrees);


    // scan right and find best for each
    reverse(all(cycle));
    reverse(all(othertrees));
    reverse(all(costs));
    // cycle is
    // {w, v->w} {v, u->v} {u, x}
    int te = cycle.back()[1];
    for(int i = m-1; i >= 1; --i)
        cycle[i][1] = cycle[i-1][1];
    cycle[0][1] = te;
    // cycle is
    // {w, x} {v, v->w} {u, u->v} = {w, x} {v, w->v} {u, v->u}
    for(int i{}; i < 8*m; ++i)
        seg[i][0] = seg[i][1] = 0;
    lb = 0;
    for(int i{1}; i < 2*m; ++i){
        pre[i] = pre[i-1] + cycle[i%m][1];
    }
    deb(cycle);
    deb(pre);
    for(int i{}; i < 2*m; ++i){
        while(lb < i && 2*(pre[i] - pre[lb]) > cytot){
            lb++;
        }
        deb(i, lb);
        
        int ret = query(1, 0, 2*m-1, lb, i-1, seg);
        if(ret >= 0){
            othertrees[i%m] = max(othertrees[i%m], ret);
        }
        update(1, costs[i%m], 0, 2*m-1, i, i, seg);
        update(1, cycle[(i+1)%m][1], 0, 2*m-1, lb, i, seg);
    }
    deb(othertrees);

    ind = 0;
    for(auto [u, c] : cycle){
        preproc(u, -1, adj);
        reroot(u, -1, dist(othertrees[ind], -1), adj);
        ind++;
    }
    for(int i{}; i < n; ++i)
        cout << out[i] << ' ';
    cout << '\n';
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
