/**
 *    author:  tourist
 *    created: 28.10.2025 12:36:11
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
class graph {
 public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  vector<edge> edges;
  vector<vector<int>> g;
  int n;

  graph(int _n) : n(_n) {
    g.resize(n);
  }

  virtual int add(int from, int to, T cost) = 0;
};

template <typename T>
class undigraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  undigraph(int _n) : graph<T>(_n) {
  }

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};

template <typename T>
class forest : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  forest(int _n) : graph<T>(_n) {
  }

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    assert(id < n - 1);
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};

template <typename T>
class dfs_forest : public forest<T> {
 public:
  using forest<T>::edges;
  using forest<T>::g;
  using forest<T>::n;

  vector<int> pv;
  vector<int> pe;
  vector<int> order;
  vector<int> pos;
  vector<int> end;
  vector<int> sz;
  vector<int> root;
  vector<int> depth;
  vector<T> dist;

  dfs_forest(int _n) : forest<T>(_n) {
  }

  void init() {
    pv = vector<int>(n, -1);
    pe = vector<int>(n, -1);
    order.clear();
    pos = vector<int>(n, -1);
    end = vector<int>(n, -1);
    sz = vector<int>(n, 0);
    root = vector<int>(n, -1);
    depth = vector<int>(n, -1);
    dist = vector<T>(n);
  }

  void clear() {
    pv.clear();
    pe.clear();
    order.clear();
    pos.clear();
    end.clear();
    sz.clear();
    root.clear();
    depth.clear();
    dist.clear();
  }

 private:
  void do_dfs(int v) {
    pos[v] = (int) order.size();
    order.push_back(v);
    sz[v] = 1;
    for (int id : g[v]) {
      if (id == pe[v]) {
        continue;
      }
      auto &e = edges[id];
      int to = e.from ^ e.to ^ v;
      depth[to] = depth[v] + 1;
      dist[to] = dist[v] + e.cost;
      pv[to] = v;
      pe[to] = id;
      root[to] = (root[v] != -1 ? root[v] : to);
      do_dfs(to);
      sz[v] += sz[to];
    }
    end[v] = (int) order.size() - 1;
  }

  void do_dfs_from(int v) {
    depth[v] = 0;
    dist[v] = T{};
    root[v] = v;
    pv[v] = pe[v] = -1;
    do_dfs(v);
  }

 public:
  void dfs(int v, bool clear_order = true) {
    if (pv.empty()) {
      init();
    } else {
      if (clear_order) {
        order.clear();
      }
    }
    do_dfs_from(v);
  }

  void dfs_all() {
    init();
    for (int v = 0; v < n; v++) {
      if (depth[v] == -1) {
        do_dfs_from(v);
      }
    }
    assert((int) order.size() == n);
  }
};

template <typename T>
vector<vector<int>> find_cycles(const graph<T> &g, int bound_cnt = 1 << 30, int bound_size = 1 << 30) {
  vector<int> was(g.n, -1);
  vector<int> st;
  vector<vector<int>> cycles;
  int total_size = 0;
  function<void(int, int)> dfs = [&](int v, int pe) {
    if ((int) cycles.size() >= bound_cnt || total_size >= bound_size) {
      return;
    }
    was[v] = (int) st.size();
    for (int id : g.g[v]) {
      if (id == pe) {
        continue;
      }
      auto &e = g.edges[id];
      int to = e.from ^ e.to ^ v;
      if (was[to] >= 0) {
        vector<int> cycle(1, id);
        for (int j = was[to]; j < (int) st.size(); j++) {
          cycle.push_back(st[j]);
        }
        cycles.push_back(cycle);
        total_size += (int) cycle.size();
        if ((int) cycles.size() >= bound_cnt || total_size >= bound_size) {
          was[v] = -2;
          return;
        }
        continue;
      }
      if (was[to] == -1) {
        st.push_back(id);
        dfs(to, id);
        st.pop_back();
      }
    }
    was[v] = -2;
  };
  for (int i = 0; i < g.n; i++) {
    if (was[i] == -1) {
      dfs(i, -1);
    }
  }
  return cycles;
}

template <typename T>
vector<int> edges_to_vertices(const graph<T> &g, const vector<int> &edge_cycle) {
  int sz = (int) edge_cycle.size();
  vector<int> vertex_cycle;
  if (sz <= 2) {
    vertex_cycle.push_back(g.edges[edge_cycle[0]].from);
    if (sz == 2) {
      vertex_cycle.push_back(g.edges[edge_cycle[0]].to);
    }
  } else {
    for (int i = 0; i < sz; i++) {
      int j = (i + 1) % sz;
      auto &e = g.edges[edge_cycle[i]];
      auto &other = g.edges[edge_cycle[j]];
      if (other.from == e.from || other.to == e.from) {
        vertex_cycle.push_back(e.to);
      } else {
        vertex_cycle.push_back(e.from);
      }
    }
  }
  return vertex_cycle;
}

template <typename T, typename F>
class SparseTable {
 public:
  int n;
  vector<vector<T>> mat;
  F func;

  SparseTable(const vector<T>& a, const F& f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  undigraph<int64_t> g(n);
  for (int i = 0; i < n; i++) {
    int a, b, d;
    cin >> a >> b >> d;
    --a; --b;
    g.add(a, b, d);
  }
  auto edge_cycle = find_cycles(g)[0];
  int sz = int(edge_cycle.size());
  vector<int64_t> coord = {0};
  for (int eid : edge_cycle) {
    coord.push_back(coord.back() + g.edges[eid].cost);
  }
  auto cycle = edges_to_vertices(g, edge_cycle);
  vector<bool> on_cycle(n, false);
  for (int x : cycle) {
    on_cycle[x] = true;
  }
  dfs_forest<int64_t> f(2 * n);
  for (auto& e : g.edges) {
    if (!on_cycle[e.from] || !on_cycle[e.to]) {
      f.add(e.from, e.to, e.cost);
    }
  }
  vector<int64_t> down;
  for (int x : cycle) {
    f.dfs(x);
    int64_t d = 0;
    for (int y : f.order) {
      d = max(d, f.dist[y]);
    }
    down.push_back(d);
  }
  vector<int64_t> dist_to_other(sz, 0);
  for (int rot = 0; rot < 2; rot++) {
    coord.resize(2 * sz);
    for (int i = 1; i < sz; i++) {
      coord[sz + i] = coord[i] + coord[sz];
    }
    vector<int64_t> val(2 * sz);
    for (int i = 0; i < 2 * sz; i++) {
      val[i] = coord[i] + down[i % sz];
    }
    SparseTable st(val, [&](int64_t x, int64_t y) { return max(x, y); });
    int ptr = 0;
    for (int i = 0; i < sz; i++) {
      while ((coord[ptr + 1] - coord[i]) * 2 <= coord[sz]) {
        ptr += 1;
      }
      if (i + 1 <= ptr) {
        dist_to_other[i] = max(dist_to_other[i], st.get(i + 1, ptr) - coord[i]);
      }
    }
    reverse(down.begin() + 1, down.end());
    reverse(dist_to_other.begin() + 1, dist_to_other.end());
    reverse(coord.begin() + 1, coord.begin() + sz);
    for (int i = 1; i < sz; i++) {
      coord[i] = coord[sz] - coord[i];
    }
  }
  vector<int64_t> ans(2 * n, 0);
  for (int i = 0; i < sz; i++) {
    int x = cycle[i];
    f.add(x, n + x, dist_to_other[i]);
    f.dfs(x);
    int diam_u = x;
    for (int y : f.order) {
      if (f.dist[y] > f.dist[diam_u]) {
        diam_u = y;
      }
    }
    f.dfs(diam_u);
    int diam_v = x;
    for (int y : f.order) {
      ans[y] = max(ans[y], f.dist[y]);
      if (f.dist[y] > f.dist[diam_v]) {
        diam_v = y;
      }
    }
    f.dfs(diam_v);
    for (int y : f.order) {
      ans[y] = max(ans[y], f.dist[y]);
    }
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " \n"[i == n - 1];
  }
  return 0;
}
