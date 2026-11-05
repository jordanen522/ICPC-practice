#include <array>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct innertreedist {
  vector<int64_t> dist;
  vector<int> cn;
  innertreedist(int n) {
    dist.resize(n);
    cn.assign(n, -1);
  }
};

struct maxqueue {
  deque<int64_t> q, maxq;
  void push(int64_t x) {
    q.push_back(x);
    while(maxq.size() && maxq.back() < x) maxq.pop_back();
    maxq.push_back(x);
  }
  int64_t pop() {
    int64_t curr = q.front(); q.pop_front();
    if(maxq.front() == curr) maxq.pop_front();
    return curr;
  }
  int64_t maxpeek() {
    return maxq.front();
  }
  int size() {
    return q.size();
  }
};

int main() {
  int n;
  cin >> n;
  vector<vector<array<int, 2>>> edges(n);
  for(int i = 0; i < n; i++) {
    int a, b, d;
    cin >> a >> b >> d;
    a--; b--;
    edges[a].push_back({b, d});
    edges[b].push_back({a, d});
  }
  vector<bool> oncycle(n, true);
  {
    vector<int> deg(n);
    queue<int> q;
    for(int i = 0; i < n; i++) {
      deg[i] = edges[i].size();
      if(deg[i] == 1) q.push(i);
    }
    while(q.size()) {
      auto curr = q.front(); q.pop();
      oncycle[curr] = false;
      for(auto [nv, _]: edges[curr]) if(--deg[nv] == 1) q.push(nv);
    }
  }
  vector<int64_t> retq(n);
  vector<int64_t> disttoleaf(n, -1);
  {
    innertreedist lhs(n), rhs(n);
    int tcn = 0;
    for(int i = 0; i < n; i++) {
      if(!oncycle[i]) continue;
      vector<int> incomp;
      auto bfs = [&](int src, innertreedist& dp, bool fill) -> int {
        dp.dist[src] = 0;
        dp.cn[src] = ++tcn;
        queue<int> q;
        q.push(src);
        int ret = 0;
        int64_t bestdist = -1;
        while(q.size()) {
          int curr = q.front(); q.pop();
          if(fill) incomp.push_back(curr);
          if(dp.dist[curr] > bestdist) {
            bestdist = dp.dist[curr];
            ret = curr;
          }
          for(auto [nv, nw]: edges[curr]) {
            if(oncycle[curr] && oncycle[nv]) continue;
            if(dp.cn[nv] != tcn) {
              dp.cn[nv] = tcn;
              dp.dist[nv] = dp.dist[curr] + nw;
              q.push(nv);
            }
          }
        }
        return ret;
      };
      int lleaf = bfs(i, lhs, true);
      disttoleaf[i] = lhs.dist[lleaf];
      int rleaf = bfs(lleaf, rhs, false);
      bfs(rleaf, lhs, false);
      for(int out: incomp) {
        retq[out] = max(retq[out], max(lhs.dist[out], rhs.dist[out]));
      }
    }
  }
  int cycleroot = -1;
  {
    int64_t largestweight = -1;
    for(int i = 0; i < n; i++) {
      if(!oncycle[i]) continue;
      for(auto [j, w]: edges[i]) {
        if(!oncycle[j]) continue;
        if(w > largestweight) {
          largestweight = w;
          cycleroot = i;
        }
      }
    }
  }
  int64_t cyclelen = 0;
  for(int i = 0; i < n; i++) {
    if(!oncycle[i]) continue;
    for(auto [j, w]: edges[i]) if(j > i && oncycle[j]) cyclelen += w;
  }
  vector<int64_t> updist(n, -1);
  for(auto [orientv, orientw]: edges[cycleroot]) {
    if(!oncycle[orientv]) continue;
    vector<int> cycleord;
    cycleord.push_back(cycleroot);
    vector<int64_t> distoncycle;
    distoncycle.push_back(0);
    int curr = orientv;
    int64_t currd = orientw;
    int par = cycleroot;
    int seen = 0;
    while(true) {
      distoncycle.push_back(currd);
      cycleord.push_back(curr);
      if(curr == cycleroot) {
        if(++seen == 2) break;
      }
      int nv = -1, nw = -1;
      for(auto [candv, candw]: edges[curr]) {
        if(candv == par) continue;
        if(!oncycle[candv]) continue;
        nv = candv;
        nw = candw;
        break;
      }
      assert(nv >= 0);
      par = curr;
      curr = nv;
      currd += nw;
    }
    int lhs = 0;
    maxqueue maxq;
    maxq.push(disttoleaf[cycleroot]);
    for(int i = 1; i < cycleord.size(); i++) {
      while(2 * (distoncycle[i] - distoncycle[lhs]) > cyclelen) {
        maxq.pop();
        lhs++;
      }
      if(maxq.size()) {
        updist[cycleord[i]] = max(updist[cycleord[i]], distoncycle[i] + maxq.maxpeek());
      }
      maxq.push(disttoleaf[cycleord[i]] - distoncycle[i]);
    }
  }
  {
    innertreedist downdp(n);
    for(int i = 0; i < n; i++) {
      if(!oncycle[i]) continue;
      downdp.dist[i] = updist[i];
      downdp.cn[i] = i;
      queue<int> q;
      q.push(i);
      while(q.size()) {
        int curr = q.front(); q.pop();
        retq[curr] = max(retq[curr], downdp.dist[curr]);
        for(auto [nv, nw]: edges[curr]) {
          if(oncycle[nv]) continue;
          if(downdp.cn[nv] != i) {
            downdp.cn[nv] = i;
            downdp.dist[nv] = downdp.dist[curr] + nw;
            q.push(nv);
          }
        }
      }
    }
  }
  for(int i = 0; i < n; i++) cout << retq[i] << " \n"[i == n-1];
}
